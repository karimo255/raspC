#include "server.h"

extern int client_count;  


void increment_client_count()  {
	client_count++;
}


void decrement_client_count()  {
	client_count--;
}

int get_client_count(){
	return client_count;
}


struct cJSON *parseConfigFile(){

    char *jsfile="/etc/mein_server/config.json";
    FILE *file = fopen(jsfile, "r"); 

    cJSON *config_object=NULL;
    
    if (file!=NULL)
    {

        char *buf=(char*) malloc(1000);
        memset(buf,0,1000);

        fread(buf, 1000, 1, file);

        config_object = cJSON_Parse(buf);


        free(buf);   fclose(file);
        
    }else{
        process("config file not found!\n");

    }
    return config_object;
}



void handlePinsDirection(cJSON *js){

    cJSON *subitem = js->child;

    while (subitem)
    {
    // handle subitem
        if (subitem->child) handlePinsDirection(subitem->child);
        int pin=0,mode=0;
        mode = cJSON_GetObjectItem(subitem,"mode")->valueint;
        pin = cJSON_GetObjectItem(subitem,"pin")->valueint;
        if(mode==0){
            pinMode(pin,INPUT);
        }else{
            pinMode(pin,OUTPUT);
        }
        subitem = subitem->next;
    }
}


//check client ip



int checkIP (cJSON *whitelist,struct lws *wsi){
            const int IP_SIZE = 50;
            char client_name [IP_SIZE];
            char client_ip [IP_SIZE];
            lws_get_peer_addresses(wsi, lws_get_socket_fd(wsi),
                client_name, sizeof (client_name),
                client_ip, sizeof (client_ip));
               // printf("ip und nsme %s  %s\n",client_ip,client_name ); 

    cJSON *subitem = whitelist->child;

    while (subitem)
    {

        if(strncmp(client_ip,cJSON_Print(subitem)+1,strlen(client_ip))==0){
            return 0;
        }    
        subitem = subitem->next;
    } 

    return -1; 
}




time_t get_mtime(const char *session_file)
{


    struct stat attribut;
    if (stat(session_file, &attribut) == -1) {
        perror(session_file);
        exit(1);
    }
    return attribut.st_mtime;
}