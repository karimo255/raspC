 #include "server.h"


static char *salt="Y/";




extern int clientAuth(char *user,char *password){

	char *passwd="/etc/mein_server/passwd";

	char tmp_user[20];
	char tmp_password[20];
	char line[50];

	FILE *passwdFile = fopen(passwd, "r"); 

	
	if (passwdFile==NULL)
	{
		process("passwd not found\n");
		return -1;
	}

	int i = 0;

	

	while(i < 100 && fgets(line, sizeof(line), passwdFile) != NULL){
		sscanf(line, "%s\t%[^\n]", tmp_user, tmp_password);
		i++;

		if(strcmp(tmp_user,user)==0){
			char *hash = strdup(crypt(password, salt));
			return strcmp (tmp_password, hash)==0?0:1;
		}
	}

	fclose(passwdFile);
	

	return 1;
}




extern void saveData(char *user,char *password){
	char *passwd="/etc/mein_server/passwd";

	FILE *passwdFile = fopen(passwd, "a");

	if (passwdFile==NULL)
	{
		process("passwd not found\n");
		exit(1);
	}

	char *hash = strdup(crypt(password, salt));


	char record[strlen(user)+strlen(hash)+2];


	sprintf(record,"\n%s\t%s",user,hash);


	//printf("record45 :  %s\n",record );

	fwrite (record , sizeof(char), strlen(record), passwdFile);	


	fclose(passwdFile);


}





