/** @file cpu_freq.c
 *  @brief Function prototypes.
 *
 *  This contains the prototypes
 *  and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

#include "server.h"

#define CORES 4


int total_last[CORES]={0};
int busy_last[CORES]={0};


static char *cpu0_busy_ticks ="echo `grep ^\"cpu0\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$7+$8-$BL}'" ;
static char *cpu0_total_ticks ="echo `grep ^\"cpu0\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$5+$6+$7+$8}'" ;

static char *cpu1_busy_ticks ="echo `grep ^\"cpu1\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$7+$8-$BL}'" ;
static char *cpu1_total_ticks ="echo `grep ^\"cpu1\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$5+$6+$7+$8}'" ;

static char *cpu2_busy_ticks ="echo `grep ^\"cpu2\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$7+$8-$BL}'" ;
static char *cpu2_total_ticks ="echo `grep ^\"cpu2\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$5+$6+$7+$8}'" ;

static char *cpu3_busy_ticks ="echo `grep ^\"cpu3\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$7+$8-$BL}'" ;
static char *cpu3_total_ticks ="echo `grep ^\"cpu3\" /proc/stat` | awk -F' ' '{printf \"%.0f\",$2+$3+$4+$5+$6+$7+$8}'" ;

static char busy_ticks[50];
static char total_ticks[50];

int cpuLiveFreq(struct cpu_freq *cpu_freq){

	static FILE *fp;

	/**
	 *	cpu0
	 */

	fp = popen(cpu0_busy_ticks, "r");
	fgets(busy_ticks, 50, fp);
	double int_busy_ticks=atoi(busy_ticks);
	pclose(fp);

	fp = popen(cpu0_total_ticks, "r");
	fgets(total_ticks, 50, fp);	
	double int_total_ticks=atoi(total_ticks);
	pclose(fp);

	cpu_freq->cpu0 = 100*((int_busy_ticks-busy_last[0])/(int_total_ticks-total_last[0]));


	busy_last[0]=int_busy_ticks;
	total_last[0]=int_total_ticks;


	/**
	 *	cpu1
	 */

	fp = popen(cpu1_busy_ticks, "r");
	fgets(busy_ticks, 50, fp);
	int_busy_ticks=atoi(busy_ticks);
	pclose(fp);

	fp = popen(cpu1_total_ticks, "r");
	fgets(total_ticks, 50, fp);	
	int_total_ticks=atoi(total_ticks);
	pclose(fp);

	cpu_freq->cpu1 = 100*((int_busy_ticks-busy_last[1])/(int_total_ticks-total_last[1]));


	busy_last[1]=int_busy_ticks;
	total_last[1]=int_total_ticks;

	
	/**
	 *	cpu2
	 */

	fp = popen(cpu2_busy_ticks, "r");
	fgets(busy_ticks, 50, fp);
	int_busy_ticks=atoi(busy_ticks);
	pclose(fp);

	fp = popen(cpu2_total_ticks, "r");
	fgets(total_ticks, 50, fp);	
	int_total_ticks=atoi(total_ticks);
	pclose(fp);

	cpu_freq->cpu2 = 100*((int_busy_ticks-busy_last[2])/(int_total_ticks-total_last[2]));


	busy_last[2]=int_busy_ticks;
	total_last[2]=int_total_ticks;


	/**
	 *	cpu3
	 */

	fp = popen(cpu3_busy_ticks, "r");
	fgets(busy_ticks, 50, fp);
	int_busy_ticks=atoi(busy_ticks);
	pclose(fp);

	fp = popen(cpu3_total_ticks, "r");
	fgets(total_ticks, 50, fp);	
	int_total_ticks=atoi(total_ticks);
	pclose(fp);

	cpu_freq->cpu3 = 100*((int_busy_ticks-busy_last[3])/(int_total_ticks-total_last[3]));


	busy_last[3]=int_busy_ticks;
	total_last[3]=int_total_ticks;
			
	return 0;

}

