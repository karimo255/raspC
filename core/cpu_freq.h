/** @file cpu_freq.h
 *  @brief Function prototypes for cpu_freq.c.
 *
 *  This contains the prototypes for  cpu_freq.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

/** @struct cpu_freq cpu_freq.h "cpu_freq.h" 
 *  @brief This structure contains information about cpu like frequence,governor etc.
 *  @var cpu_freq::cpu0 
 *  Member 'cpu_cur_freq' contains cpu current frequence
 *  @var cpu_freq::cpu1 
 *  Member 'cpu_min_freq' contains cpu minimum frequence
 *  @var cpu_freq::cpu2 
 *  Member 'cpu_max_freq' contains cpu maximum frequence
 *  @var cpu_freq::cpu3 
 *  Member 'cpu_governor' contains cpu current governor
 */
struct cpu_freq{
    double cpu0;
    double cpu1;
    double cpu2;
    double cpu3;
};


/** @fn extern int cpuLiveFreq(struct cpu_freq *cpu_freq)
 *  @brief save cpu cores frequences in struct cpu_freq *cpu_freq.
 *
 *   save cpu cores frequences in struct cpu_freq *cpu_freq.
 *
 *   @param struct cpu_freq *cpu_freq.
 *
 *   @return void.
 */
extern int cpuLiveFreq(struct cpu_freq *cpu_freq);