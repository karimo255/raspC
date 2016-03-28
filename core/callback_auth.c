 #include "server.h"


static char *received_msg=NULL;

cJSON *root_copy;

char *rand_string()
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK";
    char str[33];
    memset(str,0,33);
    int n=0;
    for ( n = 0; n < 32; n++) {
        int key = rand() % (int) (sizeof charset - 1);
        str[n] = charset[key];
    }
   
    
    char *ret_str=malloc(sizeof(char)*32);
    strcpy(ret_str,str);
    
    return ret_str;
}

int callback_auth(struct lws *wsi, enum lws_callback_reasons reason, void *user,
  void *in, size_t len)  {

    struct per_session_data__auth *pss =
    (struct per_session_data__auth *)user;

    switch (reason) {
        case LWS_CALLBACK_CLOSED:
        {

        }
        case LWS_CALLBACK_ESTABLISHED:
        {
            pss->session_id=NULL;

            break;
        }
        case LWS_CALLBACK_SERVER_WRITEABLE:
        {         
            cJSON *root,*root_object;

            root = cJSON_CreateArray();
            root_object=cJSON_CreateObject();
            cJSON_AddItemToArray(root,root_object);

            if(pss->session_id){
                cJSON_AddStringToObject(root_object, "request", "session-id");            
                cJSON_AddStringToObject(root_object, "session_id", pss->session_id);
            }else{
                cJSON_AddStringToObject(root_object, "request", "default");                            
            }

            char *out=cJSON_Print(root);
            printf("out %s\n",out );

            int count = strlen(out);

            unsigned char buffer[LWS_PRE + count];
            unsigned char *p = &buffer[LWS_PRE];

            int n = sprintf((char *)p, "%s", out);

            lws_write(wsi, p,  n, LWS_WRITE_TEXT);  

            break;
        }
        case LWS_CALLBACK_RECEIVE:
        {
            received_msg = (char *) in;
          //  printf("char in %s\n",received_msg);
            root_copy = cJSON_Parse(received_msg);

            char *user  = cJSON_GetObjectItem(root_copy,"user")->valuestring;
            char *pass = cJSON_GetObjectItem(root_copy,"pass")->valuestring;

        //    printf(" user %s pass %s \n",user,pass );


            char *key = rand_string();
         //   printf("t %s\n",key );



            if(clientAuth(user,pass)==0){
                
                char *path="/etc/raspC/sessions/";
                char session_file[strlen(path)+strlen(key)+2];
                sprintf(session_file,"%s%s",path,key);


                FILE *fp = fopen(session_file, "ab+");



                char record[strlen("user")+strlen(user)+2];
                sprintf(record,"user=%s\n",user);
               // printf("record %s\n",record );

                //create session_file
                fwrite (record , sizeof(char), strlen(record), fp);

                
                pss->session_id=key;
                memcpy(pss->session_id,key,strlen(key));
                fclose(fp);                
            }
            lws_callback_on_writable (wsi);



            //saveData(user,pass);

            


            break;
        }  
        default:
        break;      

    }
    return 0;
}


