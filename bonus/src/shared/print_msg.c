/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_msg.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/03 16:03:23 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/09/26 16:07:07 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
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

void	print_msg(t_data *data, enum e_msg msg)
{
	static const char	*msgs[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking"
	};

	sem_wait(data->sema_write);
	printf("%ld %d %s\n", elapsed_time(data->start_time), data->id, msgs[msg]);
	sem_post(data->sema_write);
}
