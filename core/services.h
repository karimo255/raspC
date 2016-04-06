//services
struct services {
    char *actived[60];
    char *disactived[60];
    int count_actived;
    int count_disactived;
};

extern void servicesInfo(struct services * );
extern char *servicesJSON(struct services services_i);

extern int stop_daemon(char *daemon,char *action);
