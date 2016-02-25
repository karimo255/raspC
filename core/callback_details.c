#include "server.h"

static int chalter=0;
//static char *received_msg=NULL;

extern int cookie_lifetime;


struct ram_usage ram_l;
struct cpu_live cpu_l; 
struct cpu_freq cpu_freq;
struct net_live net_live;

struct cpu_info cpu_i;
struct storage_info storage_l;

int zeuge=0;


cJSON *root,*root_object;


int callback_details(struct lws *wsi, enum lws_callback_reasons reason, void *user,
	void *in, size_t len)  {

	struct per_session_data__details *pss =
	(struct per_session_data__details *)user; 


	switch (reason) {
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
		{            
			check_session(wsi,pss);
			break; 
		}         
		case LWS_CALLBACK_CLOSED:
		{
			chalter=0;
			decrement_client_count();
			lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));
		}
		case LWS_CALLBACK_ESTABLISHED:
		{
			pss->checked=0;
			process("*****user info down******");
			process(pss->session_id);
			process(pss->user);

			chalter=0;
			increment_client_count();
			lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

			root = cJSON_CreateArray();
			root_object=cJSON_CreateObject();
			cJSON_AddItemToArray(root,root_object);

			cJSON_AddStringToObject(root_object, "request", "count_client");            
			cJSON_AddNumberToObject(root_object, "data", get_client_count());

			char *out=cJSON_Print(root);

			int count = strlen(out);

			unsigned char buffer[LWS_PRE + count];
			unsigned char *p = &buffer[LWS_PRE];

			int n = sprintf((char *)p, "%s", out);

			lws_write(wsi, p,  n, LWS_WRITE_TEXT); 

		}
		case LWS_CALLBACK_SERVER_WRITEABLE:
		{         
			if(zeuge!=get_client_count()){
				pss->checked=0;
				zeuge=get_client_count();
			}
			if(pss->checked==0){
				storageInfo(&storage_l);
				cpuInfo(&cpu_i);

				char *out = hardwareStaticJSON(storage_l,cpu_i);


				int count = strlen(out);

				unsigned char buffer[LWS_PRE + count];
				unsigned char *p = &buffer[LWS_PRE];

				int n = sprintf((char *)p, "%s", out);


				lws_write(wsi, p,  n, LWS_WRITE_TEXT);
				free(out);           
				process("erst check");
				
				pss->checked=1;

				break;				

			}else{
				char *out = hardwareDynamicJSON(cpu_l,ram_l,cpu_freq,net_live);


				int count = strlen(out);

				unsigned char buffer[LWS_PRE + count];
				unsigned char *p = &buffer[LWS_PRE];

				int n = sprintf((char *)p, "%s", out);


				lws_write(wsi, p,  n, LWS_WRITE_TEXT);
				free(out);
			}  
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


