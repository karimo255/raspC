/* home_info */
struct home_info
{
    char ip_addr_local[32];
    char ip_addr_ext[32];
    char hostname[32];
    char os[32];
    char users[128];

};
extern int homeInfo(struct home_info *home_i);
/* end home_info */