/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_handling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 17:58:21 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:39:58 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

/*
** Time of day is capped at 1 million
** So we should add +1000 everytime it overflows
*/

struct timeval	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval);
}

/*
Miliseconds = DeltaSeconds * 1000 + DeltaMicroSeconds / 1000
*/

long	elapsed_time(struct timeval start)
{
	struct timeval	elapsed;

	elapsed = get_time();
	return ((elapsed.tv_sec - start.tv_sec) * 1000l \
		 + (elapsed.tv_usec - start.tv_usec) / 1000l);
}

/*
MicroSecond sleep, usleep(miliseconds)
*/

void	ms_sleep(long microseconds)
{
	struct timeval	entry;

	entry = get_time();
	while (elapsed_time(entry) < microseconds)
		usleep(100);
}
