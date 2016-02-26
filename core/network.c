#include "server.h"


static char *tx ="sudo cat /sys/class/net/wlan0/statistics/tx_bytes" ;
static char *rx ="sudo cat /sys/class/net/wlan0/statistics/rx_bytes" ;


static char tmp[15];

int netLive(struct net_live *net_live){

	static FILE *fp;


	fp = popen(rx, "r");
	fgets(tmp, 15, fp);

	net_live->rx = atoi(tmp)/1024;
	
	pclose(fp);//end


	fp = popen(tx, "r");
	fgets(tmp, 15, fp);

	net_live->tx = atoi(tmp)/1024;
	
	pclose(fp);//end

	net_live->total = net_live->tx+net_live->rx;
	

	return 0;

}

