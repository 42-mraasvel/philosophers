/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 08:11:20 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/10 10:20:16 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "proto.h"

static int	abort_program_init(t_data *data)
{
	free(data->children);
	return (ERR);
}

static int	program_init(t_data *data)
{
	data->children = malloc(data->input.num_philo * sizeof(pid_t));
	if (data->children == NULL)
		return (ERR);
	if (semaphore_init(data) == ERR)
		return (abort_program_init(data));
	data->start_time = get_time();
	return (OK);
}

static int	program_end(t_data *data, int exit_status)
{
	free(data->children);
	semaphores_destroy(data);
	return (exit_status);
}

/*
1. Parse args
2. Create philosophers/processes
3. Monitor processes for deaths or returns
*/

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (get_input(&data.input, argc, argv) == ERR)
		return (ERR);
	if (program_init(&data) == ERR)
		return (ERR);
	if (create_children(&data) == ERR)
		return (program_end(&data, ERR));
	monitor_children(&data);
	return (program_end(&data, OK));
}
