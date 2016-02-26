#include "server.h"

//static char *received_msg=NULL;

extern int cookie_lifetime;


extern char *hash;
extern char *new_user;



int callback_home(struct lws *wsi, enum lws_callback_reasons reason, void *user,
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
            break; 
        }         
        case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
        {
            new_user=pss->user;
            decrement_client_count();
        }   
        case LWS_CALLBACK_ESTABLISHED:
        {

            process("*****user info down*****************");
            process(pss->session_id);
            new_user=pss->user;


        }
        case LWS_CALLBACK_SERVER_WRITEABLE:
        {         
            if(strncmp(pss->checked,hash,32)!=0){
                memcpy(pss->checked,hash,32);
                process("erst check");
                
                cJSON *root,*root_object;   

                root = cJSON_CreateArray();
                root_object=cJSON_CreateObject();
                cJSON_AddItemToArray(root,root_object);

                cJSON_AddStringToObject(root_object, "request", "count_client");
                cJSON_AddStringToObject(root_object, "user", new_user);                         
                cJSON_AddNumberToObject(root_object, "data", get_client_count());

                char *out=cJSON_Print(root);

                int count = strlen(out);

                unsigned char buffer[LWS_PRE + count];
                unsigned char *p = &buffer[LWS_PRE];

                int n = sprintf((char *)p, "%s", out);

                lws_write(wsi, p,  n, LWS_WRITE_TEXT);              
                free(root);free(root_object);
                break;              

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


