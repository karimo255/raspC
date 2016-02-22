#include "server.h"




static char *cpu0 ="cat /proc/stat | awk ' $1==\"cpu0\"  {print $2 }'" ;
static char *cpu1 ="cat /proc/stat | awk ' $1==\"cpu1\"  {print $2 }'" ;
static char *cpu2 ="cat /proc/stat | awk ' $1==\"cpu2\"  {print $2 }'" ;
static char *cpu3 ="cat /proc/stat | awk ' $1==\"cpu3\"  {print $2 }'" ;


static char tmp[15];

int cpuLiveFreq(struct cpu_freq *cpu_freq){

	static FILE *fp;


	fp = popen(cpu0, "r");
	fgets(tmp, 15, fp);

	cpu_freq->cpu0 = rand()%240;
	
	pclose(fp);//end


	fp = popen(cpu1, "r");
	fgets(tmp, 15, fp);

	cpu_freq->cpu1 = rand()%240;
	
	pclose(fp);//end


	fp = popen(cpu2, "r");
	fgets(tmp, 15, fp);

	cpu_freq->cpu2 = rand()%240;
	
	pclose(fp);//end


	fp = popen(cpu3, "r");
	fgets(tmp, 15, fp);

	cpu_freq->cpu3 = rand()%240;
	
	pclose(fp);//end


	return 0;

}

