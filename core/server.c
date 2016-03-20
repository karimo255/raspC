#include "server.h"

int close_testing;
int max_poll_elements;
int debug_level = 9;

int cookie_lifetime=31*24*3600;//one week
int client_count=0; 
int old_client_count=-1; 

char *hash=NULL;
char *new_user=NULL;

char *net_interface="wlan0";

volatile int force_exit = 0;

struct client *clinets_lst;

struct lws_context *context;





enum demo_protocols {
	/* always first */
	PROTOCOL_HTTP = 0,

	PROTOCOL_HOME,
	PROTOCOL_DETAILS,
	PROTOCOL_SERVICES,
	PROTOCOL_GPIO,
	PROTOCOL_AUTH,

	/* always last */
	DEMO_PROTOCOL_COUNT
};

/* list of supported protocols and callbacks */

static struct lws_protocols protocols[] = {
	/* first protocol must always be HTTP handler */

	{
		"http-only",		/* name */
		callback_http,		/* callback */
		sizeof (struct per_session_data__http),	/* per_session_data_size */
		0,			/* max frame size / rx buffer */
	},
	{
		"home",
		callback_home,
		sizeof(struct per_session_data__details),
		1024,
	},
	{
		"details",
		callback_details,
		sizeof(struct per_session_data__details),
		1024,
	},		
	{
		"services",
		callback_services,
		sizeof(struct per_session_data__details),
		1024,
	},
	{
		"gpio",
		callback_gpio,
		sizeof(struct per_session_data__details),
		1024,
	},
	{
		"auth",
		callback_auth,
		sizeof(struct per_session_data__details),
		124,
	},	
	{ NULL, NULL, 0, 0 } /* terminator */
};



void sighandler(int sig)
{
	force_exit = 1;
	lws_cancel_service(context);
}

static const struct lws_extension exts[] = {
	{
		"permessage-deflate",
		lws_extension_callback_pm_deflate,
		"permessage-deflate"
	},
	{
		"deflate-frame",
		lws_extension_callback_pm_deflate,
		"deflate_frame"
	},
	{ NULL, NULL, NULL /* terminator */ }
};

//pares conf file  .json
cJSON *config_obj;
cJSON *ipWhitelist;
cJSON *pinDirections;

char *forbidden_message= "<body><h3>Blocked IP-ADRESSE </h3></body>";

int main(int argc, char **argv)
{
	daemonize();
	




	//saveData("admin",100,100,"admin");

	config_obj=parseConfigFile();
	ipWhitelist = cJSON_GetObjectItem(config_obj,"ipWhitelist");

	wiringPiSetup();
	pinDirections = cJSON_GetObjectItem(config_obj,"pinDirections");
	handlePinsDirection(pinDirections);

	signal(SIGINT, sighandler);
	


	struct lws_context_creation_info info;
	unsigned int ms, oldms= 0;
	const char *iface = NULL;
	char cert_path[1024];
	char key_path[1024];
	int use_ssl = 0;
	int opts = 0;
	int n = 0;

	/*
	 * take care to zero down the info struct, he contains random garbaage
	 * from the stack otherwise
	 */
	 memset(&info, 0, sizeof info);
	 info.port = 7681;


	 signal(SIGINT, sighandler);



	 info.iface = iface;
	 info.protocols = protocols;
	 info.ssl_cert_filepath = NULL;
	 info.ssl_private_key_filepath = NULL;

	 if (use_ssl) {
	 	if (strlen(resource_path) > sizeof(cert_path) - 32) {
	 		lwsl_err("resource path too long\n");
	 		return -1;
	 	}
	 	sprintf(cert_path, "%s/libwebsockets-test-server.pem",
	 		resource_path);
	 	if (strlen(resource_path) > sizeof(key_path) - 32) {
	 		lwsl_err("resource path too long\n");
	 		return -1;
	 	}
	 	sprintf(key_path, "%s/libwebsockets-test-server.key.pem",
	 		resource_path);

	 	info.ssl_cert_filepath = cert_path;
	 	info.ssl_private_key_filepath = key_path;
	 }
	 info.gid = -1;
	 info.uid = -1;
	 info.max_http_header_pool = 1;
	 info.options = opts | LWS_SERVER_OPTION_VALIDATE_UTF8;
	 info.extensions = NULL;
	 context = lws_create_context(&info);
	 if (context == NULL) {
	 	lwsl_err("libwebsocket init failed\n");
	 	return -1;
	 }



	 n = 0;

	 while (n >= 0 && !force_exit) {
	 	struct timeval tv;

	 	gettimeofday(&tv, NULL);

		/*
		 * This provokes the LWS_CALLBACK_SERVER_WRITEABLE for every
		 * live websocket connection using the DUMB_INCREMENT protocol,
		 * as soon as it can take more packets (usually immediately)
		 */
		 extern struct ram_usage ram_l;
		 extern struct cpu_live cpu_l;
		 extern struct cpu_freq cpu_freq;




		if(old_client_count!=client_count){
			if(hash){
				free(hash);
			}

			hash=rand_string();
		 	lws_callback_on_writable_all_protocol(context,
		 		&protocols[PROTOCOL_GPIO]);
		 	lws_callback_on_writable_all_protocol(context,
		 		&protocols[PROTOCOL_DETAILS]);		
		 	lws_callback_on_writable_all_protocol(context,
		 		&protocols[PROTOCOL_SERVICES]);	
		 	lws_callback_on_writable_all_protocol(context,
		 		&protocols[PROTOCOL_HOME]);			 				 			 					
			old_client_count=client_count;
		}

		 ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		 if ((ms - oldms) > 200 && get_client_count()>0 && (cpuLive(&cpu_l,5)==0 && ramLive(&ram_l,5)==0  && cpuLiveFreq(&cpu_freq)==0 )) {
		 	lws_callback_on_writable_all_protocol(context,
		 		&protocols[PROTOCOL_DETAILS]);
		 	oldms = ms;
		 }				 


		 n = lws_service(context, 50);
	}

		lws_context_destroy(context);

		lwsl_notice("libwebsockets-test-server exited cleanly\n");


		return 0;
	}
