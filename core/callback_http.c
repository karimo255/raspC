#include "server.h"
/* http server gets files from this path */
#define RESOURCE_PATH  "/share/raspC/resource"

extern int debug_level;
extern int cookie_lifetime;

enum demo_protocols {
/* always first */
    PROTOCOL_HTTP = 0,

    PROTOCOL_DUMB_INCREMENT,
    PROTOCOL_LWS_MIRROR,

/* always last */
    DEMO_PROTOCOL_COUNT
};

/*
* We take a strict whitelist approach to stop ../ attacks
*/
struct serveable {
    const char *urlpath;
    const char *mimetype;
};

struct other_headers
{
    char header[1024];
    int len;
};

int set_other_headers(struct lws *wsi,char *key, char *value,struct other_headers *other_h){
    struct timeval tv;
    unsigned char *p;
    char b64[64];
    other_h->len = 0;
    if (!lws_hdr_total_length(wsi, WSI_TOKEN_HTTP_COOKIE)) {
        gettimeofday(&tv, NULL);
        other_h->len = sprintf(b64, value,
            (unsigned int)tv.tv_sec,
            (unsigned int)tv.tv_usec);

        p = (unsigned char *)other_h->header;

        if (lws_add_http_header_by_name(wsi,
            (unsigned char *)key,
            (unsigned char *)b64, other_h->len, &p,
            (unsigned char *)other_h->header + sizeof(other_h->header)))
            return 1;
        other_h->len = (char *)p - other_h->header;
        return 0;

    }
    return 1;
    
        /* end of cookie */     
}





/* this protocol server (always the first one) handles HTTP,
*
* Some misc callbacks that aren't associated with a protocol also turn up only
* here on the first protocol server.
*/

extern cJSON *ipWhitelist;
extern char *forbidden_message;

int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user,
    void *in, size_t len) { 


    struct per_session_data__http *pss =
    (struct per_session_data__http *)user;



    switch (reason) {
        case LWS_CALLBACK_FILTER_HTTP_CONNECTION:
        {

            char *cookie=get_header_item(wsi,"cookie:");
            char *session_id=NULL;
            
            if(cookie){
                //build session_file form coockie/session_id
                session_id= strrchr(cookie, '=')+1;
                char *session_file_path="/etc/raspC/sessions";
                char session_file[sizeof(session_file_path)+sizeof(session_id)+1]={0};
                sprintf(session_file,"%s/%s",session_file_path,session_id);

                //check if sessionfile exit
                FILE *session_filep= fopen(session_file,"r");
                if(session_filep==NULL){
                    process(session_file);
                    process("sessions dir not found");
                    free(cookie);
                    break;
                }

                //check if session_file is valid
                time_t jetzt= time(NULL);
                time_t create_date = get_mtime(session_file);

                double diff = difftime(jetzt,create_date);
                if(diff>cookie_lifetime){
                    if(unlink(session_file)!=0)
                        process("session_file not removed");
                    free(cookie);
                    break;
                }


                //set session
                pss->session_id=session_id;

                
            }
            free(cookie);
            break; 
        } 
        case LWS_CALLBACK_HTTP:
        {


            if(checkIP(ipWhitelist,wsi)!=0){
                lws_return_http_status(wsi, HTTP_STATUS_FORBIDDEN, forbidden_message);
                return -1;
            }

            char *requested_uri = (char *) in;
            if (strcmp(requested_uri, "/") == 0) {
                requested_uri = "/home.html";
            }            

            char *requested_file_ext = strrchr(requested_uri,'.');

            if(!pss->session_id && strcmp(requested_file_ext,".html")==0){
                requested_uri="/auth.html";
                
            }
            

        // try to get current working directory
            char cwd[100];
            char *resource_path;

            if (getcwd(cwd, sizeof (cwd)) != NULL) {
            // allocate enough memory for the resource path
                resource_path = malloc(120);

            // join current working direcotry to the resource path
                sprintf(resource_path, "%s%s", RESOURCE_PATH, requested_uri);
               // process(resource_path);

            if( access( resource_path, F_OK ) != -1 ) { // file exists
            }else{
                requested_uri = "/404.html";

                //free(resource_path);
                // join current working direcotry to the resource path
                sprintf(resource_path, "%s%s", RESOURCE_PATH, requested_uri); 
            }

            process(resource_path);
            

            char *extension = strrchr(resource_path, '.');
            char *mime;

            // choose mime type based on the file extension
            if (extension == NULL) {
                mime = "text/plain";
            } else if (strcmp(extension, ".png") == 0) {
                mime = "image/png";
            } else if (strcmp(extension, ".jpg") == 0) {
                mime = "image/jpg";
            } else if (strcmp(extension, ".gif") == 0) {
                mime = "image/gif";
            } else if (strcmp(extension, ".html") == 0) {
                mime = "text/html";
            } else if (strcmp(extension, ".css") == 0) {
                mime = "text/css";
            } else {
                mime = "text/plain";
            }

            //struct other_headers cookie;





            lws_serve_http_file(wsi, resource_path, mime,0,0);
            free(resource_path);
            if(!pss->session_id){
                //set_other_headers(wsi,"set-cookie:","session_id=LWS_%u_%u_COOKIE;Max-Age=360000",&cookie);
                //lws_serve_http_file(wsi, resource_path, mime,cookie.header,cookie.len);
               // return 1;
            }
        }
        break;
    }

    case LWS_CALLBACK_CLOSED_HTTP:
    break;
    default:
    break;
}


return 0;
}
