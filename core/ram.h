struct ram_info {
    int total;
};


struct ram_usage {
    int used;
    int frei;
    int shared;
    int buffers;
    int cached;
};


extern void ramInfo(struct ram_info *ram_i);
extern int ramLive(struct ram_usage *ram_u,int interval);