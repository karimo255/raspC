 #include "server.h"


static int chalter=0;
static char *received_msg=NULL;



struct ram_usage ram_l;
struct cpu_live cpu_l;

struct cpu_info cpu_i;
struct storage_info storage_l;


int callback_details(struct lws *wsi, enum lws_callback_reasons reason, void *user,
  void *in, size_t len)  {

    switch (reason) {
        case LWS_CALLBACK_CLOSED:
        {
            chalter=0;
            decrement_client_count();
            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));
        }
        case LWS_CALLBACK_ESTABLISHED:
        {
            chalter=0;
            increment_client_count();
            lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

            
            storageInfo(&storage_l);
            cpuInfo(&cpu_i);

            char *out = hardwareStaticJSON(storage_l,cpu_i);

            printf("out %s\n", out );

            int count = strlen(out);

            unsigned char buffer[LWS_PRE + count];
            unsigned char *p = &buffer[LWS_PRE];

            int n = sprintf((char *)p, "%s", out);


            lws_write(wsi, p,  n, LWS_WRITE_TEXT);
            free(out);           
            

            break;
        }
        case LWS_CALLBACK_SERVER_WRITEABLE:
        {         
            
          char *out = hardwareDynamicJSON(cpu_l,ram_l);

            printf("out %s\n", out );

            int count = strlen(out);

            unsigned char buffer[LWS_PRE + count];
            unsigned char *p = &buffer[LWS_PRE];

            int n = sprintf((char *)p, "%s", out);


            lws_write(wsi, p,  n, LWS_WRITE_TEXT);
            free(out);  
            break;
        }
        case LWS_CALLBACK_RECEIVE:
        {
            //received_msg = (char *) in;
            //chalter=1;
            //lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));

            break;
        }  
        default:
        break;      

    }
    return 0;
}


