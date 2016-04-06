/** @file network.h
 *  @brief Function prototypes for network.c.
 *
 *  This contains the prototypes for  network.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

/** @struct net_live network.h "network.h" 
 *  @brief This structure contains network informations.
 *  @var net_live::tx 
 *  Member 'tx' transmitted 
 *  @var net_live::rx 
 *  Member 'rx' received
 *  @var net_live::total 
 *  Member 'total' contains cpu maximum frequence
 */
struct net_live{
    int tx;
    int rx;
    int total;
};

/** @struct net_info network.h "network.h" 
 *  @brief This structure contains network informations.
 *  @var net_info::oneline 
 *  Member 'oneline' oneline 
 *  @var net_info::interfaces 
 *  Member 'interfaces' interfaces
 */
struct net_info{
    char oneline[320];
    char interfaces[320];
};


/** @fn extern int netLive(struct net_live *net_live,char *interface)
 *  @brief save cpu network informations for interface in struct cpu_freq *cpu_freq.
 *
 *   save cpu cores frequences in struct cpu_freq *cpu_freq.
 *
 *   @param struct net_live *net_live.
 *   @param struct interface *interface. 
 *
 *   @return void.
 */
extern int netLive(struct net_live *net_live,char *interface);



/** @fn extern int netInfo(struct net_info *net_info,char *interface)
 *  @brief save cpu network informations for interface in struct cpu_freq *cpu_freq.
 *
 *   save cpu network informations for interface in struct cpu_freq *cpu_freq.
 *
 *   @param struct net_info *net_info.
 *   @param struct interface *interface.  
 *
 *   @return void.
 */
extern int netInfo(struct net_info *net_info,char *interface);