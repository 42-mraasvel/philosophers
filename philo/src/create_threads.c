/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_threads.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 08:53:09 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/09/29 16:34:02 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "proto.h"

/*
Setting philo_died to true causes all threads to return

Join that started already
*/

static int	abort_create_threads(t_data *data, int i)
{
	data->philo_died = true;
	while (i > 0)
	{
		i--;
		pthread_join(data->pthreads[i], NULL);
	}
	return (ft_error("pthread_create", "failed"));
}

/*
1 thread for each philosopher
*/

int	create_threads(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	data->started = false;
	while (i < data->input.num_philo)
	{
		data->philos[i].status = active;
		ret = pthread_create(
				&data->pthreads[i],
				NULL,
				philo_routine,
				&data->philos[i]);
		if (ret != 0)
			return (abort_create_threads(data, i));
		usleep(100);
		i++;
	}
	data->start_time = get_time();
	data->started = true;
	return (OK);
}

int	join_threads(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->input.num_philo)
	{
		ret = pthread_join(data->pthreads[i], NULL);
		if (ret != 0)
			return (ft_error("pthread_join", "error"));
		i++;
	}
	return (OK);
}
