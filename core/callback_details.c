#include "server.h"

//static char *received_msg=NULL;

extern int cookie_lifetime;


struct ram_usage ram_l;
struct cpu_live cpu_l; 
struct cpu_freq cpu_freq;
struct net_live net_live;

struct cpu_info cpu_i;
struct storage_info storage_l;
char *hash=NULL;
char *new_user;



cJSON *root,*root_object;


int callback_details(struct lws *wsi, enum lws_callback_reasons reason, void *user,
	void *in, size_t len)  {

	struct per_session_data__details *pss =
	(struct per_session_data__details *)user; 

	root = cJSON_CreateArray();
	root_object=cJSON_CreateObject();
	cJSON_AddItemToArray(root,root_object);


	switch (reason) {
		case LWS_CALLBACK_PROTOCOL_INIT:{
			break;
		}
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
		{            
			check_session(wsi,pss);
			increment_client_count();
			break; 
		}         
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
		{
			decrement_client_count();
		}	
		case LWS_CALLBACK_ESTABLISHED:
		{

			if(hash){
				free(hash);
			}

			hash=rand_string();

			process("*****user info down*****************");
			process(pss->session_id);
			new_user=pss->user;


			storageInfo(&storage_l);
			cpuInfo(&cpu_i);

			char *out = hardwareStaticJSON(storage_l,cpu_i);

			int count = strlen(out);

			unsigned char buffer[LWS_PRE + count];
			unsigned char *p = &buffer[LWS_PRE];

			int n = sprintf((char *)p, "%s", out);

			lws_write(wsi, p,  n, LWS_WRITE_TEXT);
			free(out); 

		}
		case LWS_CALLBACK_SERVER_WRITEABLE:
		{         
			if(strncmp(pss->checked,hash,32)!=0){
				memcpy(pss->checked,hash,32);
				process("erst check");

				cJSON_AddStringToObject(root_object, "request", "count_client");
				cJSON_AddStringToObject(root_object, "user", new_user);				            
				cJSON_AddNumberToObject(root_object, "data", get_client_count());

				char *out=cJSON_Print(root);

				int count = strlen(out);

				unsigned char buffer[LWS_PRE + count];
				unsigned char *p = &buffer[LWS_PRE];

				int n = sprintf((char *)p, "%s", out);

				lws_write(wsi, p,  n, LWS_WRITE_TEXT); 				

				break;				

			}

			char *out = hardwareDynamicJSON(cpu_l,ram_l,cpu_freq,net_live);

			int count = strlen(out);

			unsigned char buffer[LWS_PRE + count];
			unsigned char *p = &buffer[LWS_PRE];

			int n = sprintf((char *)p, "%s", out);


			lws_write(wsi, p,  n, LWS_WRITE_TEXT);
			free(out);
			
			break;
		}
		case LWS_CALLBACK_RECEIVE:
		{
        //received_msg = (char *) in;
        //chalter=1;
        //lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

			break;
		}  
		default:
		break;      

	}
	return 0;
}


