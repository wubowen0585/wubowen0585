#
# Regular cron jobs for the wubw package
# See dh_installcron(1) and crontab(5).
#
0 4	* * *	root	[ -x /usr/bin/wubw_maintenance ] && /usr/bin/wubw_maintenance
