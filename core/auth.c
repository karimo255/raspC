 #include "server.h"


static char *salt="Y/.U34DoL195";


extern int clientAuth(char *user,char *password){

	char *passwd="/etc/raspC/passwd";

	char tmp_user[20]={0};
	char tmp_password[20]={0};
	char uid[100]={0};
	char gid[100]={0};
	char line[150]={0};
	char deli[2];

	FILE *passwdFile = fopen(passwd, "r"); 

	
	if (passwdFile==NULL)
	{
		process("passwd not found\n");
		return -1;
	}

	int i = 0;

	

	while(i < 100 && fgets(line, sizeof(line), passwdFile) != NULL){
		sscanf(line, "%[^:]%[:^:]%[^:]%[:^:]%[^:]%[:^:]%[^\n]", tmp_user,deli,uid,deli,gid,deli,tmp_password);
		process(tmp_password);
		i++;

		if(strcmp(tmp_user,user)==0){
			char *hash = strdup(crypt(password, salt));
			return strcmp (tmp_password, hash)==0?0:1;
		}
	}

	fclose(passwdFile);
	

	return 1;
}




extern void saveData(char *user,int uid,int gid,char *password){
	char *passwd="/etc/raspC/passwd";

	FILE *passwdFile = fopen(passwd, "a");

	if (passwdFile==NULL)
	{
		process("passwd not found\n");
		exit(1);
	}

	char *hash = strdup(crypt(password, salt));




	char record[150];


	sprintf(record,"%s:%d:%d:%s\n",user,uid,gid,hash);



	//printf("record45 :  %s\n",record );

	fwrite (record , sizeof(char), strlen(record), passwdFile);	


	fclose(passwdFile);


}





