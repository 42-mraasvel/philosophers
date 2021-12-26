/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/14 17:43:13 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:50:42 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "ft_semaphore.h"
#include "proto.h"

static int	abort_process_init(t_data *data)
{
	if (data->philo)
		free(data->philo->sema_death_name);
	free(data->philo);
	return (ERR);
}

int	process_init(t_data *data)
{
	free(data->children);
	data->philo = malloc(1 * sizeof(t_philo));
	if (data->philo == NULL)
		return (ERR);
	ft_bzero(data->philo, sizeof(t_philo));
	data->philo->sema_death_name = ft_itoa(data->id);
	if (data->philo->sema_death_name == NULL)
		return (abort_process_init(data));
	sem_unlink(data->philo->sema_death_name);
	data->philo->sema_death = sem_open(
			data->philo->sema_death_name,
			O_CREAT | O_EXCL,
			0660, 1);
	if (data->philo->sema_death == SEM_FAILED)
		return (abort_process_init(data));
	data->philo->last_eaten = get_time();
	data->philo->status = inactive;
	return (OK);
}
