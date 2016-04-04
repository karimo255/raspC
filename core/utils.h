/** @file utils.h
 *  @brief Function prototypes for the utils.c.
 *
 *  This contains the prototypes for the utils.c
 *  and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

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
*	Parse Configuration File "/etc/raspC/config.json" to a cJSON Object.
*
*	@return config_object as cJSON Object.
*/
extern struct
cJSON *parseConfigFile();

/** @brief Set GPIO Pins Direction.
*
*	Set GPIO Pins Directions ("Input/Output") based on the infomation
* 	provided by "/etc/raspC/config.json" section 'pinDirections'.
*
*	@return void
*/
extern void 
handlePinsDirection(cJSON *js);

/** @brief Check IP-adresse.
*
*	Check if IP-adresse is in the whitelist structur generad from the config_obejct.
*	
*	@param cJSON *whitelist.
*	@param lws *wsi websocket instance.
*
*	@return 0 if ip listed otherwise -1.
*/
extern int
checkIP (cJSON *whitelist, struct lws *wsi);

/** @brief get the modification time of file.
*
*	get the modification time of file located at path.
*
*	@param path of file 
*
*	@return time_t modification time
*/	
time_t get_mtime(const char *path);

/** @brief get header informations.
*
*	get header infomation for a item such a cookie etc.
*
*	@param lws *wsi websocket instance.
*	@param *item.
*
*	@return header information
*/
extern char * 
get_header_item(struct lws *wsi,char *item);

/** @brief Prints user info.
*
*   Prints user info
*
*  	@param per_session_data__details *pss.
*
*  	@return Void.
*/
extern void 
dump_user_info(struct per_session_data__details *pss);

/** @brief check if session running.
*
*   check if session file existed, if not redirect client to auth
*
*	@param lws *wsi websocket instance.
*  	@param per_session_data__details *pss.
*
*  	@return 0 if session runnig otherwise -1.
*/
extern int 
check_session(struct lws *wsi,struct per_session_data__details *pss);

/** @brief parse passwd file.
*
*   parse passwd file, grep and get uid "uid" and gid "gid" for user "user"
*
*	@param lws *wsi websocket instance.
*  	@param per_session_data__details *pss.
*
*  	@return 0 if session runnig otherwise -1.
*/
extern void 
parse_passwd(char *user,char *uid,char *gid);