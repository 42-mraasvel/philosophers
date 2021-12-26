/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 09:11:19 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/09/27 17:56:33 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "proto.h"

/*
1. Set search lock
2. Grab gork 2
3. Grab fork 2
4. Unlock search lock
*/

static void	grab_forks(t_data *data)
{
	sem_wait(data->sema_search);
	sem_wait(data->sema_forks);
	print_msg(data, e_grab_fork);
	sem_wait(data->sema_forks);
	print_msg(data, e_grab_fork);
	sem_post(data->sema_search);
}

/*
1. Lock death check semaphore
2. Set last eaten time
3. Unlock death check semaphore
4. Print msg
5. Wait until eating is finished
6. Drop forks
*/

static void	philo_eat(t_data *data)
{
	sem_wait(data->philo->sema_death);
	data->philo->last_eaten = get_time();
	sem_post(data->philo->sema_death);
	print_msg(data, e_eating);
	ms_sleep(data->input.time_to_eat);
	data->philo->times_eaten += 1;
	sem_post(data->sema_forks);
	sem_post(data->sema_forks);
}

static void	philo_sleep(t_data *data)
{
	print_msg(data, e_sleeping);
	ms_sleep(data->input.time_to_sleep);
}

void	*philo_routine(void *data_ptr)
{
	t_data	*data;

	data = data_ptr;
	data->philo->last_eaten = get_time();
	while (true)
	{
		grab_forks(data);
		philo_eat(data);
		if (data->philo->times_eaten == data->input.num_times_to_eat)
			break ;
		philo_sleep(data);
		print_msg(data, e_thinking);
		usleep(1000);
	}
	data->philo->status = inactive;
	return (NULL);
}
