/** @file storage.h
 *  @brief Function prototypes for client list storage.c.
 *
 *  This contains the prototypes for the storage.c
 *  and eventually any macros, constants,
 *  or global variables needed.
 *
 *  @author Karim Echchennouf
 *  @author Ziad Benhachem
 *  @bug No known bugs.
 */

 
/** @struct storage_info storage.h "storage.h" 
 *  @brief This structure is used to build clinet list.
 *
 *  @var storage_info::total 
 *  Member 'total' total
 *  @var storage_info::used 
 *  Member 'used' used
 *  @var storage_info::free 
 *  Member 'free' free
 *
 */

//struct storage_info storage_l;


struct storage_info {
    int total;
    int used;
    int free;
};


/** @fn extern void storageInfo(struct storage_info *storage_i) 
*	@brief save storageInfo to struct storage_info *storage_i.
*
*   save storageInfo to struct storage_info *storage_i.
*
*   @param struct *storage_info. 
*
*   @return void.
*/
extern void storageInfo(struct storage_info *storage_i);