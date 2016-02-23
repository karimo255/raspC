 #include "server.h"


static int chalter=0;
//static char *received_msg=NULL;



struct ram_usage ram_l;
struct cpu_live cpu_l;

struct cpu_info cpu_i;
struct storage_info storage_l;


int callback_home(struct lws *wsi, enum lws_callback_reasons reason, void *user,
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

                      
            

            break;
        }
        case LWS_CALLBACK_SERVER_WRITEABLE:
        {         

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


