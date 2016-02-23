#include "server.h"

static int chalter=0;
//static char *received_msg=NULL;

extern int cookie_lifetime;


struct ram_usage ram_l;
struct cpu_live cpu_l; 
struct cpu_freq cpu_freq;

struct cpu_info cpu_i;
struct storage_info storage_l;





int callback_details(struct lws *wsi, enum lws_callback_reasons reason, void *user,
	void *in, size_t len)  {

	struct per_session_data__details *pss =
	(struct per_session_data__details *)user;    

	

	char *session_file_path="/etc/mein_server/sessions";



	switch (reason) {
		case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
		{            
			
			check_session(wsi,pss);
			


			//free(cookie);
			break; 
		}         
		case LWS_CALLBACK_CLOSED:
		{
			chalter=0;
			decrement_client_count();
            //lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));
		}
		case LWS_CALLBACK_ESTABLISHED:
		{
			if(pss->session_id){
				
				/* ouf */
				char session_file[75]={0};
				sprintf(session_file,"%s/%s",session_file_path,pss->session_id);

                //check if sessionfile exit
				FILE *session_filep= fopen(session_file,"r");
				if(session_filep==NULL){
					process("sessions file not found3");
					fclose(session_filep);
					break;
				}

				char line[50]={0};
				if(fgets(line, sizeof(line), session_filep) != NULL)
				{
					pss->user=strrchr(line, '=')+1;

					char uid[10];
					char gid[10];

					parse_passwd(pss->user,uid,gid);

					int u=atoi(uid);
					int g=atoi(gid);
					//int g=atoi(gid);

					process(uid);
					process(gid);
					pss->uid =u;
					pss->gid =g; 
				} 


            }     /*ouf*/
				//process(pss->user);




				chalter=0;
				increment_client_count();
			//lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

            /*   new */


            /*  new end */


				storageInfo(&storage_l);
				cpuInfo(&cpu_i);

				char *out = hardwareStaticJSON(storage_l,cpu_i);


				int count = strlen(out);

				unsigned char buffer[LWS_PRE + count];
				unsigned char *p = &buffer[LWS_PRE];

				int n = sprintf((char *)p, "%s", out);


				lws_write(wsi, p,  n, LWS_WRITE_TEXT);
				free(out);           


				break;
			}
			case LWS_CALLBACK_SERVER_WRITEABLE:
			{         

				char *out = hardwareDynamicJSON(cpu_l,ram_l,cpu_freq);


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


