/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

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

#include "home_info.h"
#include "storage.h" 
#include "cpu.h" 
#include "ram.h"  
#include "cpu_freq.h" 
#include "network.h" 
#include "services.h" 
#include "hardware_info.h" 

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




















