#include "server.h"

char *lock_path="/var/run/raspC.pid";
void process(char arr[]){

    syslog(LOG_NOTICE, arr);
} 

 


void daemonize(){
    int n, fd, ret;
    char buf[10];
    int  len, sent;
    char sz[20];

  /* init logging */
    setlogmask (LOG_UPTO (LOG_NOTICE));
    openlog ("raspC", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

        /* Our process ID and Session ID */
    pid_t pid, sid;

        /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
        /* If we got a good PID, then
           we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }



        /* Change the file mode mask */
    umask(0);

        /* Open any logs here */        

        /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
                /* Log the failure */
        exit(EXIT_FAILURE);
    }


        //lock file
    fd = open(lock_path, O_RDONLY);
    if (fd >= 0) {
        n = read(fd, buf, sizeof(buf));
        close(fd);
        if (n) {
            n = atoi(buf);
            ret = kill(n, 0);
            if (ret >= 0) {
                fprintf(stderr,
                   "Daemon already running from pid %d\n", n);
                exit(1);
            }
            fprintf(stderr,
                "Removing stale lock file %s from dead pid %d\n",
                lock_path, n);
            unlink(lock_path);
        }
    }
    close(fd);

    fd = open(lock_path, O_TRUNC | O_RDWR | O_CREAT, 0640);
    if (fd < 0) {
        fprintf(stderr,
         "unable to create lock file %s, code=%d (%s)\n",
         lock_path, errno, strerror(errno));
        exit(1);
    }
    len = sprintf(sz, "%u", sid);
    sent = write(fd, sz, len);
    if (sent != len)
        fprintf(stderr,
          "unable to write pid to lock file %s, code=%d (%s)\n",
          lock_path, errno, strerror(errno));

    close(fd);

    if (chdir("/") < 0) {
        fprintf(stderr,
            "unable to change directory to %s, code %d (%s)",
            "/", errno, strerror(errno));
        exit(1);
    }

    /* Redirect standard files to /dev/null */
    if (!freopen("/dev/null", "r", stdin))
        fprintf(stderr, "unable to freopen() stdin, code %d (%s)",
         errno, strerror(errno));

    if (!freopen("/dev/null", "w", stdout))
        fprintf(stderr, "unable to freopen() stdout, code %d (%s)",
         errno, strerror(errno));

    if (!freopen("/dev/null", "w", stderr))
        fprintf(stderr, "unable to freopen() stderr, code %d (%s)",
         errno, strerror(errno));



}
