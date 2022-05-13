#! /bin/sh
### BEGIN INIT INFO
# Provides:             chs camera app
# Required-Start:
# Required-Stop:
# Default-Start:        2 5
# Default-Stop:         0
# Short-Description:    chs camera app
# Description:          cameraapp is chs camera app
### END INIT INFO
#
# -*- coding: utf-8 -*-
# Debian init.d script for chs camera app

# Source function library.
. /etc/init.d/functions

DAEMON=/usr/bin/cameraapp
RUNDIR=/var/run/cameraapp
DESC="chs camera app"
ARGUMENTS=""

test -x $DAEMON || exit 0

#[ -z "$SYSCONFDIR" ] && SYSCONFDIR=/var/lib/cameraapp
#mkdir -p $SYSCONFDIR

check_for_no_start() {
    # forget it if we're trying to start, and /var/lib/cameraapp/camera_app_not_to_be_run exists
    if [ -e $SYSCONFDIR/camera_app_not_to_be_run ]; then
	echo "cameraapp not in use ($SYSCONFDIR/camera_app_not_to_be_run)"
	exit 0
    fi
}

check_privsep_dir() {
    # Create the PrivSep empty dir if necessary
    if [ ! -d /var/run/cameraapp ]; then
		mkdir -p $RUNDIR
    fi
}

case "$1" in
  start)
	check_for_no_start
  	echo -n "Starting $DESC: "
	check_privsep_dir
	$DAEMON $ARGUMENTS &
  	echo "done."
	;;
  stop)
  	echo -n "Stopping $DESC: "
	killall $DAEMON
  	echo "done."
	;;

  restart)
  	echo -n "Restarting $DESC: "
	killall $DAEMON
	check_for_no_start
	check_privsep_dir
	sleep 1
	$DAEMON $ARGUMENTS &
	echo "."
	;;

  status)
	status $DAEMON
	exit $?
  ;;

  *)
	echo "Usage: /etc/init.d/cameraapp {start|stop|status|restart}"
	exit 1
esac

exit 0
