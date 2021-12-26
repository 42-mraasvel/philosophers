/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forked_routine.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 08:42:31 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:49:12 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "proto.h"

static int	process_end(t_data *data, int exit_status)
{
	semaphore_destroy(data->philo->sema_death, data->philo->sema_death_name);
	free(data->philo->sema_death_name);
	free(data->philo);
	return (exit_status);
}

static int	create_philosopher(t_data *data)
{
	int	ret;

	data->philo->status = active;
	ret = pthread_create(
			&data->philo->thread,
			NULL,
			philo_routine,
			data);
	if (ret != 0)
		return (ft_error("pthread create", "failed"));
	return (OK);
}

/*
Check death time in a loop
If a philosopher died, we just lock write for output and exit
If philosopher finished eating thread is joined and returned
*/

static int	monitor_philo(t_data *data)
{
	while (1)
	{
		sem_wait(data->philo->sema_death);
		if ((int)elapsed_time(data->philo->last_eaten)
			>= data->input.time_to_die)
		{
			sem_wait(data->sema_write);
			printf("%ld %d died\n", elapsed_time(data->start_time), data->id);
			return (DIED_EXIT_STATUS);
		}
		else if (data->philo->status == inactive)
			break ;
		sem_post(data->philo->sema_death);
		usleep(1000);
	}
	pthread_join(data->philo->thread, NULL);
	return (OK);
}

/*
1. Create a single thread per process to run philosopher routine
2. Monitor said routine to check if it's died
*/

int	forked_routine(t_data *data)
{
	if (process_init(data) != OK)
		return (DIED_EXIT_STATUS);
	if (create_philosopher(data) != OK)
		return (process_end(data, DIED_EXIT_STATUS));
	if (monitor_philo(data) == DIED_EXIT_STATUS)
		return (process_end(data, DIED_EXIT_STATUS));
	return (process_end(data, OK));
}
