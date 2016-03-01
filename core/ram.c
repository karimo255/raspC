#include "server.h"

time_t retTime;
void waitFor (unsigned int secs) {
    retTime = time(0) + secs;     // Get finishing time.
    while (time(0) < retTime);    // Loop until it arrives.
}
void ramInfo(struct ram_info *ram_i) {

	char *ram_total ="free -mo | awk ' NR==2  {print $2 }'" ;

	FILE *fp;
	char tmp[15];

	fp = popen(ram_total, "r");
	fgets(tmp, 15, fp);
	ram_i->total = atoi(tmp);

	pclose(fp);
}


static char *ram_used ="free -mo | awk ' NR==2  {print $3 }'" ;
static char *ram_free ="free -mo | awk ' NR==2  {print $4 }'" ;
static char *ram_shared ="free -mo | awk ' NR==2  {print $5 }'" ;
static char *ram_buffers ="free -mo | awk ' NR==2  {print $6 }'" ;
static char *ram_cached ="free -mo | awk ' NR==2  {print $7 }'" ;

static char tmp[15];

int ramLive(struct ram_usage *ram_u,int interval){




	static FILE *fp;


	fp = popen(ram_used, "r");
	fgets(tmp, 15, fp);

	ram_u->used = atoi(tmp);
	
	pclose(fp);

	fp = popen(ram_free, "r");
	fgets(tmp, 15, fp);

	ram_u->frei = atoi(tmp);

	
	pclose(fp);	

	fp = popen(ram_shared, "r");
	fgets(tmp, 15, fp);
	
	ram_u->shared = atoi(tmp); 
	
	pclose(fp);

	fp = popen(ram_buffers, "r");
	fgets(tmp, 15, fp);
	
	ram_u->buffers = atoi(tmp); 	
	
	pclose(fp);

	fp = popen(ram_cached, "r");
	fgets(tmp, 15, fp);
	
	ram_u->cached = atoi(tmp); 	
	

	pclose(fp);

	return 0;

}

