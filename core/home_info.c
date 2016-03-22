#include "server.h"


void homeInfo(struct home_info *home_i) {

	char *ip_addr_local ="free -mo | awk ' NR==2  {print $2 }'" ;
	char *ip_addr_ext ="free -mo | awk ' NR==2  {print $2 }'" ;
	char *hostname="";
	char *os="";
	char *users="";

	FILE *fp;
	char tmp[15];

	fp = popen(ram_total, "r");
	fgets(tmp, 15, fp);
	ram_i->total = atoi(tmp);

	pclose(fp);
}




