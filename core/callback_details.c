#include "server.h"

//static char *received_msg=NULL;

extern int cookie_lifetime;


struct ram_usage ram_l;
struct cpu_live cpu_l; 
struct cpu_freq cpu_freq;
struct net_live net_live;

struct cpu_info cpu_i;
struct storage_info storage_l;

extern char *hash;
extern char *new_user;

extern struct client *clinets_lst;




int callback_details(struct lws *wsi, enum lws_callback_reasons reason, void *user,
	void *in, size_t len)  {

	struct per_session_data__details *pss =
	(struct per_session_data__details *)user; 




	switch (reason) {
		case LWS_CALLBACK_PROTOCOL_INIT:{
			break;
		}
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
		{            
			check_session(wsi,pss);
			increment_client_count();
			if(lst_find(&clinets_lst,pss->uid)<0){
				lst_append(&clinets_lst, pss->user,pss->uid,pss->gid,pss->session_id+24);
			}				
			break; 
		}         
		case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
		{
			new_user=pss->user;
			decrement_client_count();
			lst_remove(&clinets_lst,pss->uid);
		}	
		case LWS_CALLBACK_ESTABLISHED:
		{

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
				
				char *out = lst_json(&clinets_lst);

				int count = strlen(out);

				unsigned char buffer[LWS_PRE + count];
				unsigned char *p = &buffer[LWS_PRE];

				int n = sprintf((char *)p, "%s", out);

				lws_write(wsi, p,  n, LWS_WRITE_TEXT); 	
				process(out);
				free(out);			
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


