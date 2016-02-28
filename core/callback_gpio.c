 #include "server.h"

static int chalter=0;
static char *received_msg=NULL;

extern char *hash;
extern char *new_user;

extern struct client *clinets_lst;


int callback_gpio(struct lws *wsi, enum lws_callback_reasons reason, void *user,
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

            dump_user_info(pss);
            
            new_user=pss->user;


            cJSON *config_obj=parseConfigFile();

            int status,pin;
            int pins[] = {0, 1, 2, 3, 4, 5,21};

            struct cJSON *root,*root_object,*root_object_array,*pinDirections;

            root = cJSON_CreateArray();
            root_object=cJSON_CreateObject();
            cJSON_AddItemToArray(root,root_object);
            root_object_array= cJSON_CreateArray(); 

            pinDirections = cJSON_GetObjectItem(config_obj,"pinDirections"); 

            cJSON_AddStringToObject(root_object, "request", "pin-init");            
            cJSON_AddItemToObject(root_object, "pinDirections", cJSON_Parse(cJSON_Print(pinDirections)));
            cJSON_AddItemToObject(root_object, "data", root_object_array);
            cJSON * prev;

            for (pin = 0; pin < sizeof (pins) / sizeof (pins[0]); ++pin) {
                status = digitalRead(pins[pin]);
                cJSON *root_object_array_object = cJSON_CreateObject();
                cJSON_AddNumberToObject(root_object_array_object, "pin", pins[pin]);
                cJSON_AddNumberToObject(root_object_array_object, "status", status);
                if (!pin) root_object_array->child = root_object_array_object;
                else prev->next = root_object_array_object, root_object_array_object->prev = prev;
                prev = root_object_array_object;
            }
            
            char *out=cJSON_Print(root);

            int count = strlen(out);

            unsigned char buffer[LWS_PRE + count];
            unsigned char *p = &buffer[LWS_PRE];

            int n = sprintf((char *)p, "%s", out);


            lws_write(wsi, p,  n, LWS_WRITE_TEXT);
            free(root);free(root_object);free(root_object_array);free(config_obj);

            break;
        }
        case LWS_CALLBACK_SERVER_WRITEABLE:
        {            

            if(strncmp(pss->checked,hash,32)!=0){
                memcpy(pss->checked,hash,32);
                
                char *out = lst_json(&clinets_lst);

                int count = strlen(out);

                unsigned char buffer[LWS_PRE + count];
                unsigned char *p = &buffer[LWS_PRE];

                int n = sprintf((char *)p, "%s", out);

                lws_write(wsi, p,  n, LWS_WRITE_TEXT);  
                free(out);  
                    
                break;              

            }

            cJSON *root,*root_object,*root_object_object;

            root = cJSON_CreateArray();
            root_object=cJSON_CreateObject();
            cJSON_AddItemToArray(root,root_object);
            root_object_object= cJSON_CreateObject(); 
             
            int pin = 0, status = 0;
            cJSON * root_copy ;
            char *out;


            root_copy = cJSON_Parse(received_msg);

            pin = cJSON_GetObjectItem(root_copy,"pin")->valueint;
            status = cJSON_GetObjectItem(root_copy,"status")->valueint;


            digitalWrite(pin, status);
            status = digitalRead(pin);


            cJSON_AddStringToObject(root_object, "request", "pin-state");            
            cJSON_AddItemToObject(root_object, "data", root_object_object); 


            cJSON_AddNumberToObject(root_object_object,"pin",pin);
            cJSON_AddNumberToObject(root_object_object,"status",status);
            out=cJSON_Print(root);

            int count = strlen(out);

            unsigned char buffer[LWS_PRE + count];
            unsigned char *p = &buffer[LWS_PRE];

            int n = sprintf((char *)p, "%s", out);
            lws_write(wsi, p,  n, LWS_WRITE_TEXT);


            free(root);free(root_object);free(root_object_object);

            break;
        }
        case LWS_CALLBACK_RECEIVE:
        {
            received_msg = (char *) in;
            chalter=1;
            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

            break;
        }  
        default:
        break;      

    }
    return 0;
}
