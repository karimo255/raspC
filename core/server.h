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






extern int clientAuth(char *user,char *password);


char *do_hashing(char *buffer);
int clientAuth(char *user,char *password);
void saveData(char *user,int uid,int gid,char *password);
extern char *rand_string();



/* daemonize */
extern void process(char arr[]);
extern void daemonize();



/** client list information */

struct client

{   
    int uid ;                 /** user id   */
    char name[20];            /** client name  */
    int gid;                  /** client name  */  
    char session_id[10];      /** session id */  
    struct client *next;      /* pointer to next client */

};

/** @brief prints information about all clients in client list.
*
*   prints information about all clients in client list.
*
*   @param struct client.
*
*   @return Void.
*/
extern void 
lst_print(const struct client* );

/** @brief append new client to client list.
*
*   append new client to client list.
*
*   @param struct *client. 
*
*   @return index of the new client beginning by 0.
*/
extern int 
lst_append(struct client **, char *,int,int,char *);

/** @brief replace client by new client.
*
*   append new client to list of connected clients.
*
*   @param struct *client.
*   @param char *user. 
*   @param int uid. 
*   @param int gid.  
*   @param char *session_id.  
*
*   @return index of the new client by success otherwise -1.
*/
extern int 
lst_replace(struct client **, char *,int,int,char *);

/** @brief check if client exists.
*
*   check if client with uid exists.
*
*   @param struct *client.
*   @param int uid. 
*
*   @return index of the client if exists otherwise -1.
*/
extern int 
lst_find(struct client **,int uid);

/** @brief remove client.
*
*   remove client from client list.
*
*   @param struct *client.
*   @param int uid. 
*
*   @return index of the client removed  otherwise -1.
*/
extern int 
lst_remove(struct client **,int uid);

/** @brief get client count.
*
*   get client count in client list.
*
*   @param struct *client.
*
*   @return client count.
*/
extern int 
lst_count(struct client **lst);

/** @brief get client list as json string.
*
*   get client list as json string.
*
*   @param struct *client.
*
*   @return json string.
*/
extern char 
*lst_json(struct client **lst);
/* list end */



/** one of these is auto-created for each connection and a pointer to the
 *  appropriate instance is passed to the callback in the user parameter
 */
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

/** @brief Increment the count of clients.
*
*   Increment the count of clients connected by one.
*
*   @return Void.
*/
extern void
increment_client_count();

/** @brief Decrement the count of clients.
*
*   Decrement the count of clients connected by one.
*
*   @return Void.
*/
extern void
decrement_client_count();

/** @brief get the count of clients.
*
*   get the count of clients connected.
*
*   @return count of clients connected.
*/
extern int
get_client_count();

/** @brief Parse Configuration File.
*
*   Parse Configuration File "/etc/raspC/config.json" to a cJSON Object.
*
*   @return config_object as cJSON Object.
*/
extern struct
cJSON *parseConfigFile();

/** @brief Set GPIO Pins Direction.
*
*   Set GPIO Pins Directions ("Input/Output") based on the infomation
*   provided by "/etc/raspC/config.json" section 'pinDirections'.
*
*   @return void
*/
extern void 
handlePinsDirection(cJSON *js);

/** @brief Check IP-adresse.
*
*   Check if IP-adresse is in the whitelist structur generad from the config_obejct.
*   
*   @param cJSON *whitelist.
*   @param lws *wsi websocket instance.
*
*   @return 0 if ip listed otherwise -1.
*/
extern int
checkIP (cJSON *whitelist, struct lws *wsi);

/** @brief get the modification time of file.
*
*   get the modification time of file located at path.
*
*   @param path of file 
*
*   @return time_t modification time
*/  
time_t get_mtime(const char *path);

/** @brief get header informations.
*
*   get header infomation for a item such a cookie etc.
*
*   @param lws *wsi websocket instance.
*   @param *item.
*
*   @return header information
*/
extern char * 
get_header_item(struct lws *wsi,char *item);

/** @brief Prints user info.
*
*   Prints user info
*
*   @param per_session_data__details *pss.
*
*   @return Void.
*/
extern void 
dump_user_info(struct per_session_data__details *pss);

/** @brief check if session running.
*
*   check if session file existed, if not redirect client to auth
*
*   @param lws *wsi websocket instance.
*   @param per_session_data__details *pss.
*
*   @return 0 if session runnig otherwise -1.
*/
extern int 
check_session(struct lws *wsi,struct per_session_data__details *pss);

/** @brief parse passwd file.
*
*   parse passwd file, grep and get uid "uid" and gid "gid" for user "user"
*
*   @param lws *wsi websocket instance.
*   @param per_session_data__details *pss.
*
*   @return 0 if session runnig otherwise -1.
*/
extern void 
parse_passwd(char *user,char *uid,char *gid);