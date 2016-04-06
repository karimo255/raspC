/** @file auth.h
 *  @brief Function prototypes for auth.h.
 *
 *  This contains the prototypes for  auth.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */


/** @brief authenticate user.
*
*   authenticate user by user and password.
*
*   @param char *user username
*   @param char *password password
*
*   @return on succes 0 otherwise 1.
*/
extern int clientAuth(char *user,char *password);

/** @brief save user data.
*
*   save user data in file "/etc/raspC/passwd.
*
*   @param char *user username
*   @param int uid user id
*   @param int gid group id
*   @param char *password password
*
*   @return void.
*/
extern void saveData(char *user,int uid,int gid,char *password);

/** @brief get random string.
*
*   get random string with 32 character.
*
*
*   @return char *random_string.
*/
extern char *rand_string();
