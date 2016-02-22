#include "server.h"



static int chalter=0;
static char *received_msg=NULL;


int callback_services(struct lws *wsi, enum lws_callback_reasons reason, void *user,
    void *in, size_t len)  {




    static char *daemon=NULL;
    static char *action=NULL;
    static char *status=NULL;

    switch (reason) {
        case LWS_CALLBACK_CLOSED:
        {
            chalter=0;
            decrement_client_count();
            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));


        }
        case LWS_CALLBACK_ESTABLISHED:
        {
            chalter=0;
            increment_client_count();
            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));


            struct services services_i;
            servicesInfo(&services_i);
            char *out = servicesJSON(services_i);
            int count = strlen(out);

            unsigned char buffer[LWS_PRE + count];
            unsigned char *p = &buffer[LWS_PRE];

            int n = sprintf((char *)p, "%s", out);
            lws_write(wsi, p,  n, LWS_WRITE_TEXT);      



            break;
        }
        case LWS_CALLBACK_SERVER_WRITEABLE:
        {       
            cJSON *root,*root_object,*root_object_object;
            root = cJSON_CreateArray();
            root_object=cJSON_CreateObject();
            cJSON_AddItemToArray(root,root_object);
            root_object_object= cJSON_CreateObject();  

            switch(chalter){
                case 0:{
                    cJSON_AddStringToObject(root_object, "request", "count_client");            
                    cJSON_AddNumberToObject(root_object, "data", get_client_count());

                    char *out=cJSON_Print(root);

                    int count = strlen(out);

                    unsigned char buffer[LWS_PRE + count];
                    unsigned char *p = &buffer[LWS_PRE];

                    int n = sprintf((char *)p, "%s", out);

                    lws_write(wsi, p,  n, LWS_WRITE_TEXT); 
                    break;
                }
                case 1:{

                    cJSON_AddStringToObject(root_object, "request", "daemon-stat");            
                    cJSON_AddItemToObject(root_object, "data", root_object_object); 



                    cJSON_AddStringToObject(root_object_object,"daemon",daemon);
                    cJSON_AddStringToObject(root_object_object,"status",status);

                    char *out=cJSON_Print(root);

                    int count = strlen(out);

                    unsigned char buffer[LWS_PRE + count];
                    unsigned char *p = &buffer[LWS_PRE];

                    int n = sprintf((char *)p, "%s", out);
                    lws_write(wsi, p,  n, LWS_WRITE_TEXT);
                    break;

                }

            }
            free(root);free(root_object);free(root_object_object);

            break;
        }
        case LWS_CALLBACK_RECEIVE:
        {
            received_msg = (char *) in;
            chalter=1;

            cJSON *root_copy= cJSON_Parse(received_msg);

            daemon = cJSON_GetObjectItem(root_copy,"daemon")->valuestring;
            action = cJSON_GetObjectItem(root_copy,"action")->valuestring;

            stop_daemon(daemon,action);

            status = strcmp(action,"stop")==0?"stoped":"started";            

            free(root_copy);

            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));


            break;
        }  
        default:
        break;      

    }
    return 0;
}


