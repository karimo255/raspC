#include "server.h"


static char *tx ="sudo cat /sys/class/net/%s/statistics/tx_bytes" ;
static char *rx ="sudo cat /sys/class/net/%s/statistics/rx_bytes" ;


static char tmp[124];

int netLive(struct net_live *net_live,char *interface){

	static FILE *fp;

	char rx_cmd[124];
	sprintf(rx_cmd,rx,interface);

	fp = popen(rx_cmd, "r");
	fgets(tmp, 124, fp);

	net_live->rx = atoi(tmp)/1024;
	
	pclose(fp);//end

	char tx_cmd[124];
	sprintf(tx_cmd,tx,interface);
	fp = popen(tx_cmd, "r");
	fgets(tmp, 124, fp);

	net_live->tx = atoi(tmp)/1024;
	
	pclose(fp);//end

	net_live->total = net_live->tx+net_live->rx;


	return 0;

}

static char *oneline="vnstat --oneline -i %s";
static char *interfaces="vnstat --iflist";

static char tmp2[320];
static char tmp3[320];

int netInfo(struct net_info *net_info,char *interface){

	static FILE *fp;

	char oneline_cmd[320];
	sprintf(oneline_cmd,oneline,interface);
	fp = popen(oneline_cmd, "r");
	fgets(tmp2, 320, fp);

	strcpy(net_info->oneline,tmp2);	
	pclose(fp);//end


	fp = popen(interfaces, "r");
	fgets(tmp3, 320, fp);

	strcpy(net_info->interfaces,tmp3+22);
	process(net_info->interfaces);	// after 22 char , ignore text "Available iterfaces :"
	pclose(fp);//end

	return 0;
}

