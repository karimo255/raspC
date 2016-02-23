#include "server.h"



void servicesInfo(struct services *services_i) {

	const char *actived_cmd ="/usr/sbin/service --status-all | awk '/ [+] /{ print $4  }'" ;
	const char *disactived_cmd ="/usr/sbin/service --status-all | awk '/ - /{ print $4  }'" ;

	FILE *fp;
	char *s ;
	char *tmp;

	fp = popen(actived_cmd, "r");
	int i=0;
	do 	{
		tmp=(char *)malloc(50);
		s=fgets(tmp, 50, fp);		
		services_i->actived[i]=tmp;
		i++;
	}while(s);
	services_i->count_actived=i;

	fp = popen(disactived_cmd, "r");
	i=0;
	do 	{
		tmp=(char *)malloc(50);
		s=fgets(tmp, 50, fp);		
		services_i->disactived[i]=tmp;
		i++;
	}while(s);	
	services_i->count_disactived=i;
	fclose(fp);

}

char *servicesJSON(struct services services_i){
	static cJSON *root,*root_object,*root_object_object;

	root = cJSON_CreateArray();

	root_object=cJSON_CreateObject();
	cJSON_AddItemToArray(root,root_object);

	root_object_object=cJSON_CreateObject();

	cJSON_AddStringToObject(root_object, "request", "services");            
	cJSON_AddItemToObject(root_object, "data", root_object_object); 

	cJSON *root_object_object_array_actived = cJSON_CreateArray();
	cJSON_AddItemToObject(root_object_object, "actived", root_object_object_array_actived); 

	cJSON *root_object_object_array_disactived = cJSON_CreateArray();
	cJSON_AddItemToObject(root_object_object, "disactived", root_object_object_array_disactived);    
	int i=0;
	for (i = 0; i < services_i.count_actived-1; ++i)
	{
		cJSON *string =cJSON_CreateString(services_i.actived[i]);
		cJSON_AddItemToArray(root_object_object_array_actived,string);
		free(services_i.actived[i]);
	}

	i=0;
	for (i = 0; i < services_i.count_disactived-1; ++i)
	{
		cJSON *string =cJSON_CreateString(services_i.disactived[i]);
		cJSON_AddItemToArray(root_object_object_array_disactived,string);
		free(services_i.disactived[i]);
	}	


	char *storagejs=NULL;
	storagejs = (char *) realloc (storagejs,strlen(cJSON_Print(root))*sizeof(char));      
	storagejs=cJSON_Print(root);


	free(root);free(root_object);free(root_object_object);free(root_object_object_array_actived),free(root_object_object_array_disactived);    
	return storagejs;
}

int stop_daemon(char *daemon,char *action){

	char start_command[50];
	char stop_command[50];

	sprintf(start_command,"service %s  start",daemon);
	sprintf(stop_command,"service %s  stop",daemon);
	printf("strt %s\n",start_command );	printf("stop %s\n",stop_command );

	if(strcmp(action,"start")==0){
		system(start_command);
	}else{
		system(stop_command);
	}

	return 0;
}


