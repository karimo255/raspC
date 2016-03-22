#include "lws_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>
#include <libwebsockets.h>
#include <cJSON.h>

#include <getopt.h>
#include <signal.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#include <unistd.h>
#include <crypt.h>

#include <sys/types.h>

#include <errno.h>
#include <syslog.h>


extern int close_testing;
extern int max_poll_elements;

#ifdef EXTERNAL_POLL
extern struct lws_pollfd *pollfds;
extern int *fd_lookup;
extern int count_pollfds;
#endif
extern volatile int force_exit;
extern struct lws_context *context;
extern char *resource_path;

extern void test_server_lock(int care);
extern void test_server_unlock(int care);

#ifndef __func__
#define __func__ __FUNCTION__
#endif




struct per_session_data__http {
	char  *session_id;
};

struct per_session_data__details {
    char  *session_id;
    char *user;
    int uid;
    int gid;
    char checked[32];
    char interface[10];
};

struct per_session_data__auth {
    char  *session_id;
};

struct per_session_data__gpio {
	int number;
};
struct per_session_data__services {
    int number;
};

struct per_session_data__lws_mirror {
	struct lws *wsi;
	int ringbuffer_tail;
};

struct per_session_data__echogen {
	size_t total;
	size_t total_rx;
	int fd;
	int fragsize;
	int wr;
};





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

extern void
dump_handshake_info(struct lws *wsi);


extern void
increment_client_count();

extern void
decrement_client_count();

extern int get_client_count();



extern struct cJSON *parseConfigFile();


extern void handlePinsDirection(cJSON *js);

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


extern int checkIP (cJSON *whitelist, struct lws *wsi);




extern int clientAuth(char *user,char *password);


char *do_hashing(char *buffer);
int clientAuth(char *user,char *password);
void saveData(char *user,int uid,int gid,char *password);
extern char *rand_string();

time_t get_mtime(const char *path);


/* daemonize */
extern void process(char arr[]);
extern void daemonize();


extern char * 
get_header_item(struct lws *wsi,char *item);
extern int 
check_session(struct lws *wsi,struct per_session_data__details *pss);

extern void 
parse_passwd(char *user,char *uid,char *gid);

/* liste */

struct client

{   int uid ;
    char name[20];            /* der Wert des clients          */
    int gid;
    char session_id[10];
    struct client *next; /* Zeiger auf das nächste client */

};


extern void lst_print(const struct client* );

extern int lst_append(struct client **, char *,int,int,char *);

extern int lst_replace(struct client **, char *,int,int,char *);
extern int lst_find(struct client **,int);
extern int lst_remove(struct client **,int);
extern int lst_count(struct client **lst);
extern char *lst_json(struct client **lst);
/* list end */

/* dump user informtion */

extern void dump_user_info(struct per_session_data__details *pss);