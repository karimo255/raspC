#include "server.h"

extern int client_count;  

extern int cookie_lifetime;

void increment_client_count()  {
	client_count++;
}


void decrement_client_count()  {

	client_count--;
    process("nach");
}

int get_client_count(){
	return client_count;
}


struct cJSON *parseConfigFile(){

    char *jsfile="/etc/raspC/config.json";
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


char * 
get_header_item(struct lws *wsi,char *item)
{
    int n = 0;
    char buf[256];
    const unsigned char *c;

    do {
      c = lws_token_to_string(n);

      if (!c) {
         n++;
         continue;
     }



     if(strncmp((char *)c,item,strlen(item))==0){
        memset(buf, 0, sizeof buf);
        lws_hdr_copy(wsi, buf, sizeof buf, n);
        if(strlen(buf)>5){
            buf[sizeof(buf) - 1] = '\0';

            char *buf_malloc = (char *)realloc(buf_malloc,256*sizeof(char));

            memcpy(buf_malloc,buf,256);
            return buf_malloc;
        }
    }

    n++;
} while (c);

return NULL;
}

void dump_user_info(struct per_session_data__details *pss){
    process("****user info****");
    process("session_id :");
    process(pss->session_id);
    process("user name :");
    process(pss->user);
    process("uid :");
    char uid[10];
    sprintf(uid,"%d",pss->uid);
    process(uid);
    process("gid :");
    char gid[10];
    sprintf(gid,"%d",pss->gid);
    process(gid);   
    process("id :");
    process(pss->session_id+24);
    process("**************************************");
}

int 
check_session(struct lws *wsi,struct per_session_data__details *pss)   
{

    char *session_file_path="/etc/raspC/sessions";

    char *cookie=get_header_item(wsi,"cookie:");

    if(cookie && !pss->session_id)
    {
        
        //build session_file form coockie/session_id        
        char *session_id= strrchr(cookie, '=')+1;


        char session_file[75]={0};
        sprintf(session_file,"%s/%s",session_file_path,session_id);

        

                //check if sessionfile exit
        FILE *session_filep= fopen(session_file,"r");
        if(session_filep==NULL){
            process("sessions file not found2");
            free(cookie);fclose(session_filep);
            return -1;
        }

        //check if session_file is valid
        time_t jetzt= time(NULL);
        time_t create_date = get_mtime(session_file);

        double diff = difftime(jetzt,create_date);
        if(diff>cookie_lifetime){
            if(unlink(session_file)!=0)
                process("session_file not removed");
            free(cookie);fclose(session_filep);
            return -1;
        }

        //set session;
        pss->session_id=session_id;
        pss->user=(char*)malloc(32);

        

        char line[100]={0};
        


        if(fgets(line, sizeof(line), session_filep) != NULL)
        {
            char *u=strrchr(line, '=')+1;
            memcpy(pss->user,u,20);
            

            char uid[10];
            char gid[10];

            parse_passwd(pss->user,uid,gid);

            
            pss->uid =atoi(uid);
            pss->gid =atoi(gid);
            memcpy(pss->checked,"init",32);             
        }else{
            process("doch");
        }         


        fclose(session_filep);
        return 0;
    }
    return -1;
}

void parse_passwd(char *user,char uid[],char gid[])
{
    FILE *passwdFile = fopen("/etc/raspC/passwd", "r"); 
    char line[75]={0};
    char deli[2];
    char tmp_user[25];
    char rest[50];
    char tmp_uid[10];
    char tmp_gid[10];

    
    if (passwdFile==NULL)
        process("passwd not found\n");
    
    int i=0;

    while(i<100 && fgets(line, sizeof(line), passwdFile) != NULL){
        memset(tmp_user,0,sizeof(tmp_user));
        sscanf(line, "%[^:]%[^\n]", tmp_user,rest);

        if(strncmp(tmp_user,user,sizeof(user))==0){
            sscanf(rest, "%[:^:]%[^:]%[:^:]%[^:]",deli,tmp_uid,deli,tmp_gid);
            memcpy(uid,tmp_uid,10);
            memcpy(gid,tmp_gid,10);
            break;
        }
        
        i++;
    }


    fclose(passwdFile);
}