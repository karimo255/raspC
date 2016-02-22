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

    switch (reason) {
        case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
        {            
            char *cookie=get_header_item(wsi,"cookie:");
            char *session_id=NULL;
            
            if(cookie){
                //build session_file form coockie/session_id
                session_id= strrchr(cookie, '=')+1;
                char *session_file_path="/etc/mein_server/sessions";

                char session_file[50]={0};
                sprintf(session_file,"%s/%s",session_file_path,session_id);

                process(session_id);

                //check if sessionfile exit
                FILE *session_filep= fopen(session_file,"r");
                if(session_filep==NULL){
                    process("sessions file not found");
                    free(cookie);
                    return -1;
                }

                //check if session_file is valid
                time_t jetzt= time(NULL);
                time_t create_date = get_mtime(session_file);

                double diff = difftime(jetzt,create_date);
                if(diff>cookie_lifetime){
                    if(unlink(session_file)!=0)
                        process("session_file not removed");
                    free(cookie);
                    return -1;
                }


                //set session
                pss->session_id=session_id;

                
            }
            free(cookie);
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

            char *session_file_path="/etc/mein_server/sessions";

            char session_file[50]={0};
            sprintf(session_file,"%s/%s",session_file_path,pss->session_id);

            FILE *sessionFile = fopen(session_file, "r"); 
            char line[150]={0};
            char *user=0;

            if (sessionFile==NULL)
                process("passwd not found\n");


            while(fgets(line, sizeof(line), sessionFile) != NULL){
                user= strrchr(line, '=')+1;
            }

            pss->user=user;


            fclose(sessionFile);            

            char uid[10];
            char gid[10];


            parse_passwd(user,uid,gid);     

            pss->uid=atoi(uid);
            pss->gid=atoi(gid);  


            process(uid);
            
            chalter=0;
            increment_client_count();
            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

            /*   new */


            /*  new end */
            

            storageInfo(&storage_l);
            cpuInfo(&cpu_i);

            char *out = hardwareStaticJSON(storage_l,cpu_i);

            printf("out %s\n", out );

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


