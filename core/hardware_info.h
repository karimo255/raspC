/** @file hardware_info.h
 *  @brief Function prototypes for the hardware_info.c.
 *
 *  This contains the prototypes for the hardware_info.c
 *  and eventually any macros, constants,
 *  or global variables need.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

extern char *hardwareStaticJSON(struct storage_info storage_l,struct cpu_info cpu_i,struct net_info net_info);
extern char *hardwareDynamicJSON(struct cpu_live cpu_l,struct ram_usage ram_l,struct cpu_freq cpu_freq,struct net_live net_live);