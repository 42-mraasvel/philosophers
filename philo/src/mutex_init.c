/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 08:40:04 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 16:04:20 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "proto.h"

static int	abort_mutex_init(t_data *data, int i, int time)
{
	ft_error("pthread_mutex_init", "failed");
	if (time > 0)
		pthread_mutex_destroy(&data->fork_locks[i]);
	if (time > 1)
		pthread_mutex_destroy(&data->philos[i].search_lock);
	while (i > 0)
	{
		i--;
		pthread_mutex_destroy(&data->fork_locks[i]);
		pthread_mutex_destroy(&data->philos[i].search_lock);
		pthread_mutex_destroy(&data->philos[i].death_lock);
	}
	return (ERR);
}

/*
Locks:
	1 for writing
	1 for each fork
	1 for each philosopher
*/

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].times_eaten = 0;
		if (pthread_mutex_init(&data->fork_locks[i], NULL) != 0)
			return (abort_mutex_init(data, i, 0));
		else if (pthread_mutex_init(&data->philos[i].search_lock, NULL) != 0)
			return (abort_mutex_init(data, i, 1));
		else if (pthread_mutex_init(&data->philos[i].death_lock, NULL) != 0)
			return (abort_mutex_init(data, i, 2));
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (abort_mutex_init(data, i + 1, 0));
	return (OK);
}

/*
Destructor for all mutexes
*/

void	mutex_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.num_philo)
	{
		pthread_mutex_destroy(&data->fork_locks[i]);
		pthread_mutex_destroy(&data->philos[i].search_lock);
		pthread_mutex_destroy(&data->philos[i].death_lock);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
}
