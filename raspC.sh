#!/bin/sh

set -e

NAME=raspC
PIDFILE=/var/run/$NAME.pid
DAEMON=/usr/sbin/raspC

export PATH="${PATH}:/usr/sbin:/sbin"
. /lib/lsb/init-functions
case "$1" in
  start)
        log_daemon_msg "$NAME started"
	start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON 
        echo "."
	;;
  stop)
        log_daemon_msg "$NAME stoped"
	start-stop-daemon --stop --quiet --oknodo --pidfile $PIDFILE
	;;
  restart)
        log_daemon_msg "$NAME restarting"
	start-stop-daemon --stop --quiet --oknodo --retry 30 --pidfile $PIDFILE
	start-stop-daemon --start --quiet --pidfile $PIDFILE --exec $DAEMON -- $DAEMON_OPTS
	;;
  status)
	status_of_proc -p $PIDFILE $DAEMON $NAME && exit 0 || exit $?
        exit $?
        ;;

  *)
	log_failure_msg "Usage: "$1" {start|stop|restart|status}"
	exit 1
esac

exit 0

