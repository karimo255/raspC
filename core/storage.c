#include "server.h"

void storageInfo(struct storage_info *storage_i) {

	char *storage_total ="df | awk ' $1==\"/dev/root\"  {print $2 }'" ;
	char *storage_used  ="df | awk ' $1==\"/dev/root\"  {print $3 }'" ;
	char *storage_free  ="df | awk ' $1==\"/dev/root\"  {print $4 }'" ;



	FILE *fp;
	char tmp[50];

	fp = popen(storage_total, "r");
	fgets(tmp, 50, fp);
	storage_i->total = atoi(tmp)/1024;

	fp = popen(storage_used, "r");
	fgets(tmp, 50, fp);
	storage_i->used = atoi(tmp)/1024;

	fp = popen(storage_free, "r");
	fgets(tmp, 50, fp);
	storage_i->free = atoi(tmp)/1024;


	pclose(fp);
}


