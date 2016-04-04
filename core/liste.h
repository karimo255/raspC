/** @file liste.c
 *  @brief Function prototypes for client list.
 *
 *  This contains the prototypes for the liste.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

 
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
