/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 16:03:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 16:15:27 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "proto.h"

static size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr_fd(int fd, char *str)
{
	return ((int)(write(fd, str, ft_strlen(str))));
}

/*
Any change of status of a philosopher must be written as follows
(with X replaced with the philosopher number and
timestamp_in_ms the current timestamp in milliseconds)

	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is sleeping
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died

Format:
	time_stamp_in_ms X [MSG]
*/

void	print_msg(t_philo *philo, enum e_msg msg)
{
	static const char	*msgs[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	pthread_mutex_lock(&philo->data->write_lock);
	if (!philo->data->philo_died)
	{
		printf("%ld %d %s\n",
			elapsed_time(philo->data->start_time), philo->id, msgs[msg]);
		if (msg == e_died)
			philo->data->philo_died = true;
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}
