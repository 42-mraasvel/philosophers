/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/14 16:01:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 16:18:53 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "proto.h"

void	*monitor_routine(void *philo_ref)
{
	t_philo	*philo;

	philo = philo_ref;
	while (!philo->data->philo_died)
	{
		if (philo->status == inactive)
			break ;
		pthread_mutex_lock(&philo->death_lock);
		if (elapsed_time(philo->last_eaten) >= philo->data->input.time_to_die)
			print_msg(philo, e_died);
		pthread_mutex_unlock(&philo->death_lock);
		usleep(1000);
	}
	return (NULL);
}
