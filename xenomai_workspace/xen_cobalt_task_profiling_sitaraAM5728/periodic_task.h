/*--------------------------- PERIODIC_TASK.h ----------------------------
 |  File periodic_task.h
 |
 |  Description: Provides functions for giving periodicity to threads 
 |
 |  Source: Slightly modified from code at: 
 |          https://2net.co.uk/tutorial/periodic_threads#ref_1
 |
 |  Version: 1V
 *-----------------------------------------------------------------------*/


#ifndef PERIODIC_TASK_H_
#define PERIODIC_TASK_H_


#include <sys/time.h>
#include <sys/timerfd.h>

struct periodic_info{
	int timer_fd;
	unsigned long long wakeups_missed;
};


static int make_periodic(unsigned int period, struct periodic_info *info){
	int ret;
	unsigned int ns;
	unsigned int sec;
	int fd;
	struct itimerspec itval;

	/* Create the timer */
	fd = timerfd_create (CLOCK_MONOTONIC, 0);
	info->wakeups_missed = 0;
	info->timer_fd = fd;
	if (fd == -1)
		return fd;

	/* Make the timer periodic */
	sec = period/1000000;
	ns = (period - (sec * 1000000)) * 1000;
	itval.it_interval.tv_sec = sec;
	itval.it_interval.tv_nsec = ns;
	itval.it_value.tv_sec = sec;
	itval.it_value.tv_nsec = ns;
	ret = timerfd_settime (fd, 0, &itval, NULL);
	return ret;
}

static void wait_period(struct periodic_info *info){
	unsigned long long missed;
	int ret;

	/* Wait for the next timer event. If we have missed any the
	   number is written to "missed" */
	ret = read (info->timer_fd, &missed, sizeof (missed));
	if (ret == -1){
		perror ("read timer");
		return;
	}

	/* "missed" should always be >= 1, but just to be sure, check it is not 0 anyway */
	if (missed > 0)
		info->wakeups_missed += (missed - 1);
}



#endif /* PERIODIC_TASK_H_ */

