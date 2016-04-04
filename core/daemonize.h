/** @file daemonize.h
 *  @brief Function prototypes for daemonize.c.
 *
 *  This contains the prototypes for  daemonize.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */


 /** @brief write to syslog.
*
*   one way to write in syslog.
*
*   @param char *msg.
*
*   @return Void.
*/
extern void process(char *msg);

 /** @brief making a daemon.
*
*   let the server runnig a background service.
*
*   @return Void.
*/
extern void daemonize();