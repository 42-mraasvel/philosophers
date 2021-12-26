/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/08 08:22:25 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 16:14:52 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "proto.h"

/*
Since free checks null pointers this is fine
*/

static int	abort_program_init(t_data *data)
{
	ft_error("program_init", "failed");
	free(data->philos);
	free(data->fork_locks);
	free(data->pthreads);
	return (ERR);
}

static int	program_init(t_data *data)
{
	data->philos = malloc(data->input.num_philo * sizeof(t_philo));
	if (data->philos == NULL)
		return (ft_perror("malloc"));
	data->fork_locks = malloc(data->input.num_philo * sizeof(pthread_mutex_t));
	if (data->fork_locks == NULL)
		return (abort_program_init(data));
	data->pthreads = malloc(data->input.num_philo * sizeof(pthread_t));
	if (data->fork_locks == NULL)
		return (abort_program_init(data));
	if (mutex_init(data) == ERR)
		return (abort_program_init(data));
	data->start_time = get_time();
	return (OK);
}

/*
Free all allocated memory and destroy all mutexes
*/

static int	program_end(t_data *data, int exit_status)
{
	mutex_destroy(data);
	free(data->philos);
	free(data->fork_locks);
	free(data->pthreads);
	return (exit_status);
}

/*
1. Read input from arguments
2. Initialize program (malloc for arrays and initialize mutex locks)
3. Start the philosopher threads
4. Monitor threads (Checking if a philosopher died mostly)
5. Join threads and clean up program once threads finished (if they ever finish)
*/

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (get_input(&data.input, argc, argv) == ERR)
		return (ERR);
	if (program_init(&data) == ERR)
		return (ERR);
	if (create_threads(&data) == ERR)
		return (program_end(&data, ERR));
	join_threads(&data);
	return (program_end(&data, 0));
}
