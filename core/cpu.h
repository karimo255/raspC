/** @file cpu.h
 *  @brief Function prototypes for cpu.c.
 *
 *  This contains the prototypes for  cpu.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

/** @struct cpu_info cpu.h "cpu.h" 
 *  @brief This structure contains information about cpu like frequence,governor etc.
 *  @var cpu_info::cpu_cur_freq 
 *  Member 'cpu_cur_freq' contains cpu current frequence
 *  @var cpu_info::cpu_min_freq 
 *  Member 'cpu_min_freq' contains cpu minimum frequence
 *  @var cpu_info::cpu_max_freq 
 *  Member 'cpu_max_freq' contains cpu maximum frequence
 *  @var cpu_info::cpu_governor 
 *  Member 'cpu_governor' contains cpu current governor
 */
struct cpu_info {
    int cpu_cur_freq;
    int cpu_min_freq;
    int cpu_max_freq;
    char cpu_governor[20];
};

/** @struct cpu_usage cpu.h "cpu.h" 
 *  @brief This structure contains information about cpu time.
 *  @var cpu_usage::user 
 *  Member 'user' contains user cpu time 
 *  @var cpu_usage::system 
 *  Member 'system' contains system cpu time 
 *  @var cpu_usage::idle 
 *  Member 'idle' contains idle cpu time 
 *  @var cpu_usage::wait 
 *  Member 'wait' contains wait cpu time 
 */
struct cpu_usage {
    int user;
    int system;
    int idle;
    int wait;
};

/** @struct cpu_live cpu.h "cpu.h" 
 *  @brief This structure contains struct cpu_usage and  cpu temperature.
 *  @var cpu_live::cpu_temp 
 *  Member 'cpu_temp' contains  cpu temperature 
 *  @var cpu_live::cpu_usage 
 *  Member 'cpu_usage' contains @struct cpu_usage 
 */
struct cpu_live {
    int cpu_temp;
    struct cpu_usage cpu_usage;
};

struct cpu_info cpu_i;
struct cpu_live cpu_l;

/** @fn void cpuInfo(struct cpu_info *cpu_i)
 *  @brief save cpu information like frequence,governor etc in struct cpu_info *cpu_i  .
 *
 *   save cpu information like frequence,governor etc in struct cpu_info *cpu_i  .
 *
 *   @param struct cpu_info *cpu_i. 
 *
 *   @return void.
 */
extern void cpuInfo(struct cpu_info *cpu_i);

/** @fn extern int cpuLive(struct cpu_live *cpu_l,int interval)
 *  @brief save cpu time and temperature in struct cpu_live *cpu_l.
 *
 *   save cpu time and temperature in struct cpu_live *cpu_l.
 *
 *   @param struct cpu_live *cpu_l.
 *   @param int interval update interval in seconds.
 *
 *   @return void.
 */
extern int cpuLive(struct cpu_live *cpu_l,int interval);