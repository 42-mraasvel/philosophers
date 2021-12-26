/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_children.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 08:39:52 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/18 07:55:29 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "proto.h"

/*
Kill all child processes created so far in case of error
*/

static void	abort_create_children(t_data *data, int i)
{
	while (i > 0)
	{
		i--;
		kill(data->children[i], SIGKILL);
	}
}

/*
Create a process for each philosopher
*/

int	create_children(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->input.num_philo)
	{
		data->children[i] = fork();
		if (data->children[i] == -1)
		{
			abort_create_children(data, i);
			return (ft_perror("fork"));
		}
		if (data->children[i] == 0)
		{
			data->id = i + 1;
			exit(forked_routine(data));
		}
		i++;
	}
	return (OK);
}

/*
If a philosopher died, we kill all other processes and return
*/

static void	kill_children(t_data *data, pid_t pid)
{
	int	i;

	i = 0;
	while (i < data->input.num_philo)
	{
		if (data->children[i] != pid)
			kill(data->children[i], SIGKILL);
		i++;
	}
}

/*
Waiting for children, check if philosopher died also
*/

void	monitor_children(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < data->input.num_philo)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == DIED_EXIT_STATUS)
				kill_children(data, pid);
		i++;
	}
}
