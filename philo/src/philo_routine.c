/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 08:59:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/09/29 16:34:38 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "proto.h"

/*
Only search for forks if the neighbours are not searching (lock neighbour)
Lock the right and left fork
1. Lock neighbours' search locks (to prevent deadlock and starvation)
2. Grab forks if available

philo->id % 2 is to prevent deadlock
*/

static void	grab_forks(t_philo *philo)
{
	int	indexes[2];

	indexes[0] = left_index(philo);
	indexes[1] = right_index(philo);
	if (philo->id % 2 == 0)
		ft_swap_int(&indexes[0], &indexes[1]);
	// pthread_mutex_lock(&philo->data->philos[indexes[1]].search_lock);
	// pthread_mutex_lock(&philo->data->philos[indexes[0]].search_lock);
	pthread_mutex_lock(&philo->data->fork_locks[indexes[0]]);
	print_msg(philo, e_grab_fork);
	pthread_mutex_lock(&philo->data->fork_locks[indexes[1]]);
	print_msg(philo, e_grab_fork);
	// pthread_mutex_unlock(&philo->data->philos[indexes[0]].search_lock);
	// pthread_mutex_unlock(&philo->data->philos[indexes[1]].search_lock);
}

/*
Reset time last eaten
Eat
Drop forks
*/

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->death_lock);
	print_msg(philo, e_eating);
	ms_sleep(philo->data->input.time_to_eat, philo);
	philo->times_eaten += 1;
	pthread_mutex_unlock(&philo->data->fork_locks[left_index(philo)]);
	pthread_mutex_unlock(&philo->data->fork_locks[right_index(philo)]);
}

static int	init_monitor(t_philo *philo)
{
	int	ret;

	ret = pthread_create(&philo->monitor, NULL, monitor_routine, philo);
	if (ret != 0)
	{
		philo->data->philo_died = true;
		return (ERR);
	}
	return (OK);
}

/*
Single philosopher simulation edge case
Simply pick up the only fork and wait for death
*/

static void	*single_philosopher(t_philo *philo)
{
	print_msg(philo, e_grab_fork);
	ms_sleep(philo->data->input.time_to_die, philo);
	return (NULL);
}

/*
Main philosopher loop
Grab Forks -> Eat -> Drop Forks -> Sleep -> Think -> Repeat

The inactive status at the end is used to break out of the monitoring loop
*/

void	*philo_routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = philo_ptr;
	if (philo->data->input.num_philo == 1)
		return (single_philosopher(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_eaten = get_time();
	if (init_monitor(philo) == ERR)
		return (NULL);
	while (true)
	{
		if (philo->data->philo_died)
			break ;
		grab_forks(philo);
		philo_eat(philo);
		if (philo->times_eaten == philo->data->input.num_times_to_eat)
			break ;
		print_msg(philo, e_sleeping);
		ms_sleep(philo->data->input.time_to_sleep, philo);
		print_msg(philo, e_thinking);
		usleep(1000);
	}
	philo->status = inactive;
	pthread_join(philo->monitor, NULL);
	return (NULL);
}
