#include "server.h"


char *hardwareStaticJSON(struct storage_info storage_l,struct cpu_info cpu_i,struct net_info net_info){
    cJSON *root,*root_object,*root_object2,*root_object_object,*root_object_object2,*root_object3,*root_object_object3;

    root = cJSON_CreateArray();

    root_object=cJSON_CreateObject();
    cJSON_AddItemToArray(root,root_object);

    root_object_object=cJSON_CreateObject();

    cJSON_AddStringToObject(root_object, "request", "storage-info");            
    cJSON_AddItemToObject(root_object, "data", root_object_object); 

    cJSON_AddNumberToObject(root_object_object, "total", storage_l.total);            
    cJSON_AddNumberToObject(root_object_object, "used", storage_l.used);            
    cJSON_AddNumberToObject(root_object_object, "free", storage_l.free); 


    root_object2=cJSON_CreateObject();
    cJSON_AddItemToArray(root,root_object2);
    root_object_object2=cJSON_CreateObject();

    cJSON_AddStringToObject(root_object2, "request", "cpu-info");            
    cJSON_AddItemToObject(root_object2, "data", root_object_object2);  

    cJSON_AddNumberToObject(root_object_object2, "cpu_cur_freq", cpu_i.cpu_cur_freq);            
    cJSON_AddNumberToObject(root_object_object2, "cpu_min_freq", cpu_i.cpu_min_freq);            
    cJSON_AddNumberToObject(root_object_object2, "cpu_max_freq", cpu_i.cpu_max_freq);                
    cJSON_AddStringToObject(root_object_object2, "cpu_governor", cpu_i.cpu_governor);

    root_object3=cJSON_CreateObject();
    cJSON_AddItemToArray(root,root_object3);

    root_object_object3=cJSON_CreateObject();

    cJSON_AddStringToObject(root_object3, "request", "network-info");            
    cJSON_AddItemToObject(root_object3, "data", root_object_object3); 
    
    cJSON_AddStringToObject(root_object_object3, "oneline", net_info.oneline);    
    cJSON_AddStringToObject(root_object_object3, "interfaces", net_info.interfaces);    
            

    
    char *storagejs=NULL;
    storagejs = (char *) realloc (storagejs,sizeof(cJSON_Print(root)));      
    storagejs=cJSON_Print(root);

    process(storagejs);
    
    
    free(root);free(root_object);free(root_object2);free(root_object3);free(root_object_object3);free(root_object_object),free(root_object_object2);    
    return storagejs;
}


char *hardwareDynamicJSON(struct cpu_live cpu_l,struct ram_usage ram_l,struct cpu_freq cpu_freq,struct net_live net_live){
    cJSON *root;
    cJSON *cpu_root_object,*cpu_root_object_object;
    cJSON *ram_root_object,*ram_root_object_object;
    cJSON *cpu_freq_root_object,*cpu_freq_root_object_object;
    cJSON *net_root_object,*net_root_object_object;

    root = cJSON_CreateArray();



    cpu_root_object=cJSON_CreateObject();
    cJSON_AddItemToArray(root,cpu_root_object);

    cpu_root_object_object=cJSON_CreateObject();

    cJSON_AddStringToObject(cpu_root_object, "request", "cpu-live");            
    cJSON_AddItemToObject(cpu_root_object, "data", cpu_root_object_object); 

    cJSON_AddNumberToObject(cpu_root_object_object, "temp", cpu_l.cpu_temp);            
    cJSON_AddNumberToObject(cpu_root_object_object, "user", cpu_l.cpu_usage.user);            
    cJSON_AddNumberToObject(cpu_root_object_object, "system", cpu_l.cpu_usage.system);            
    cJSON_AddNumberToObject(cpu_root_object_object, "idle", cpu_l.cpu_usage.idle);            
    cJSON_AddNumberToObject(cpu_root_object_object, "wait", cpu_l.cpu_usage.wait);  



    ram_root_object=cJSON_CreateObject();
    cJSON_AddItemToArray(root,ram_root_object);

    ram_root_object_object=cJSON_CreateObject();

    cJSON_AddStringToObject(ram_root_object, "request", "ram-live");            
    cJSON_AddItemToObject(ram_root_object, "data", ram_root_object_object); 

    cJSON_AddNumberToObject(ram_root_object_object, "used", ram_l.used);            
    cJSON_AddNumberToObject(ram_root_object_object, "free", ram_l.frei);            
    cJSON_AddNumberToObject(ram_root_object_object, "shared", ram_l.shared);            
    cJSON_AddNumberToObject(ram_root_object_object, "buffers", ram_l.buffers);            
    cJSON_AddNumberToObject(ram_root_object_object, "cached", ram_l.cached); 


    cpu_freq_root_object=cJSON_CreateObject();
    cJSON_AddItemToArray(root,cpu_freq_root_object);

    cpu_freq_root_object_object=cJSON_CreateObject();

    cJSON_AddStringToObject(cpu_freq_root_object, "request", "cpu-freq");            
    cJSON_AddItemToObject(cpu_freq_root_object, "data", cpu_freq_root_object_object); 

    cJSON_AddNumberToObject(cpu_freq_root_object_object, "cpu0", cpu_freq.cpu0);            
    cJSON_AddNumberToObject(cpu_freq_root_object_object, "cpu1", cpu_freq.cpu1);            
    cJSON_AddNumberToObject(cpu_freq_root_object_object, "cpu2", cpu_freq.cpu2);            
    cJSON_AddNumberToObject(cpu_freq_root_object_object, "cpu3", cpu_freq.cpu3);            



    net_root_object=cJSON_CreateObject();
    cJSON_AddItemToArray(root,net_root_object);

    net_root_object_object=cJSON_CreateObject();

    cJSON_AddStringToObject(net_root_object, "request", "net-live");            
    cJSON_AddItemToObject(net_root_object, "data", net_root_object_object); 

    cJSON_AddNumberToObject(net_root_object_object, "tx", net_live.tx);            
    cJSON_AddNumberToObject(net_root_object_object, "rx", net_live.rx);            
    cJSON_AddNumberToObject(net_root_object_object, "total", net_live.total);            


    
    char *hardwarejs=NULL;
    hardwarejs = (char *) realloc (hardwarejs,strlen(cJSON_Print(root))*sizeof(char));      
    hardwarejs=cJSON_Print(root);
    

    free(root);
    free(cpu_root_object);free(cpu_root_object_object);
    free(ram_root_object);free(ram_root_object_object); 
    free(cpu_freq_root_object);free(cpu_freq_root_object_object);
    free(net_root_object);free(net_root_object_object);

    return hardwarejs;
}