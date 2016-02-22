#include "server.h"
char *cpu_cur_freq = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq";
char *cpu_min_freq = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq";
char *cpu_max_freq = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq";
char *cpu_governor = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";

void cpuInfo(struct cpu_info *cpu_i) {




	FILE *fp;
	char tmp[15];
	memset(tmp,0,15);


	fp = popen(cpu_cur_freq, "r");
	fgets(tmp, 15, fp);
	cpu_i->cpu_cur_freq = atoi(tmp) / 1000;
	pclose(fp);

	fp = popen(cpu_min_freq, "r");
	fgets(tmp, 15, fp);
	cpu_i->cpu_min_freq = atoi(tmp) / 1000;
	pclose(fp);

	fp = popen(cpu_max_freq, "r");
	fgets(tmp, 15, fp);
	cpu_i->cpu_max_freq = atoi(tmp) / 1000;
	pclose(fp);

	fp = popen(cpu_governor, "r");
	fgets(tmp, 15, fp);

	strcpy(cpu_i->cpu_governor,tmp);  

	pclose(fp);

}


static char *cpu_temp_cmd="cat /sys/class/thermal/thermal_zone0/temp";
static char *cpu_usage_user ="vmstat | awk ' NR==3  {print $13 }'" ;
static char *cpu_usage_system ="vmstat | awk ' NR==3  {print $14 }'" ;
static char *cpu_usage_idle ="vmstat | awk ' NR==3  {print $15 }'" ;
static char *cpu_usage_wait ="vmstat | awk ' NR==3  {print $16 }'" ;

char tmp[15];   

int cpuLive(struct cpu_live *cpu_l,int interval){



	static FILE *fp;

	fp = popen(cpu_temp_cmd, "r");
	fgets(tmp, 15, fp);
	
	cpu_l->cpu_temp = atoi(tmp)/1000;   	
	
	pclose(fp);


	fp = popen(cpu_usage_user, "r");
	fgets(tmp, 15, fp);
	
	cpu_l->cpu_usage.user = atoi(tmp); 	
	
	pclose(fp);


	fp = popen(cpu_usage_system, "r");
	fgets(tmp, 15, fp);
	
	cpu_l->cpu_usage.system  = atoi(tmp); 	
	pclose(fp);


	fp = popen(cpu_usage_idle, "r");
	fgets(tmp, 15, fp);
	
	cpu_l->cpu_usage.idle = atoi(tmp); 
	pclose(fp);

	fp = popen(cpu_usage_wait, "r");
	fgets(tmp, 15, fp);
	
	cpu_l->cpu_usage.wait = atoi(tmp);  
	
	pclose(fp);

	return 0;

}

