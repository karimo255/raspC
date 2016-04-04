/** @file server.h
 *  @brief Function prototypes for the server.c.
 *
 *  This contains the prototypes for the server.c
 *  and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <getopt.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <crypt.h>
#include <wiringPi.h>
#include <libwebsockets.h>
#include <cJSON.h>

#include "liste.h"
#include "utils.h"
#include "auth.h"
#include "daemonize.h"

extern int close_testing;

extern volatile int force_exit;

/** resource path for http requests
 */
extern char *resource_path;

/** 
* callable callbacks ,they are called by the loop in the main program in server.c
*/
extern int
callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user,
   void *in, size_t len);
extern int
callback_home(struct lws *wsi, enum lws_callback_reasons reason,
    void *user, void *in, size_t len);
extern int
callback_details(struct lws *wsi, enum lws_callback_reasons reason,
    void *user, void *in, size_t len);

extern int
callback_services(struct lws *wsi, enum lws_callback_reasons reason,
   void *user, void *in, size_t len);
extern int
callback_gpio(struct lws *wsi, enum lws_callback_reasons reason,
   void *user, void *in, size_t len);

extern int
callback_auth(struct lws *wsi, enum lws_callback_reasons reason,
   void *user, void *in, size_t len);

/** @brief Prints infos about handshake with client.
*
*   The Output contains a lot of information about the client.
*   One way to build filter.
*
*  @param struct lws *wsi The websocket instanze.
*  @return Void.
*/
extern void
dump_handshake_info(struct lws *wsi);



//cpu

struct cpu_info {
    int cpu_cur_freq;
    int cpu_min_freq;
    int cpu_max_freq;
    char cpu_governor[20];
};


struct cpu_usage {
    int user;
    int system;
    int idle;
    int wait;
};

//cpu freq
struct cpu_freq{
    int cpu0;
    int cpu1;
    int cpu2;
    int cpu3;
};

extern int cpuLiveFreq(struct cpu_freq *cpu_freq);

//network
struct net_live{
    int tx;
    int rx;
    int total;
};

extern int netLive(struct net_live *net_live,char *interface);

//network
struct net_info{
    char oneline[320];
    char interfaces[320];
};

extern int netInfo(struct net_info *net_info,char *interface);


//

struct cpu_live {
    int cpu_temp;
    struct cpu_usage cpu_usage;
};

/* home_info */
struct home_info
{
    char ip_addr_local[32];
    char ip_addr_ext[32];
    char hostname[32];
    char os[32];
    char users[128];

};
extern int homeInfo(struct home_info *home_i);
/* end home_info */

struct ram_info {
    int total;
};


struct ram_usage {
    int used;
    int frei;
    int shared;
    int buffers;
    int cached;
};

//hardware

struct ram_usage ram_l;


struct cpu_live cpu_l;
struct cpu_info cpu_i;

struct storage_info storage_l;

extern void cpuInfo(struct cpu_info *cpu_i);


extern int cpuLive(struct cpu_live *cpu_l,int interval);

//storage

struct storage_info {
    int total;
    int used;
    int free;
};

extern void ramInfo(struct ram_info *ram_i);
extern int ramLive(struct ram_usage *ram_u,int interval);

extern void storageInfo(struct storage_info *storage_i);



//hardware-info

extern char *hardwareStaticJSON(struct storage_info storage_l,struct cpu_info cpu_i,struct net_info net_info);
char *hardwareDynamicJSON(struct cpu_live cpu_l,struct ram_usage ram_l,struct cpu_freq cpu_freq,struct net_live net_live);

//services
struct services {
    char *actived[60];
    char *disactived[60];
    int count_actived;
    int count_disactived;
};

extern void servicesInfo(struct services * );
extern char *servicesJSON(struct services services_i);

extern int stop_daemon(char *daemon,char *action);
//check client ip















