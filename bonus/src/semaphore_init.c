/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphore_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/10 08:26:22 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:41:13 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_semaphore.h"
#include "proto.h"

void	semaphore_destroy(sem_t *semaphore, char *name)
{
	if (semaphore == NULL)
		return ;
	sem_close(semaphore);
	sem_unlink(name);
}

static int	abort_semaphore_init(t_data *data)
{
	semaphore_destroy(data->sema_forks, SEMA_FORK);
	semaphore_destroy(data->sema_write, SEMA_WRITE);
	semaphore_destroy(data->sema_search, SEMA_SEARCH);
	return (ft_error("semaphore_open failed", NULL));
}

void	semaphores_destroy(t_data *data)
{
	semaphore_destroy(data->sema_forks, SEMA_FORK);
	semaphore_destroy(data->sema_write, SEMA_WRITE);
	semaphore_destroy(data->sema_search, SEMA_SEARCH);
}

/*
1. Unlink to make sure the semaphore doesn't yet exit
2. Open/create semaphores with permissions

	Write semaphore: locks writing (1 count)
	Search semaphore: locks picking up forks: prevent deadlock and starvation
	Fork semaphore: 1 for each fork: prevents usage of more than num_philo forks
*/

int	semaphore_init(t_data *data)
{
	sem_unlink(SEMA_FORK);
	sem_unlink(SEMA_WRITE);
	sem_unlink(SEMA_SEARCH);
	data->sema_forks = sem_open(SEMA_FORK, O_CREAT | O_EXCL,
			0660, data->input.num_philo);
	if (data->sema_forks == SEM_FAILED)
		return (ERR);
	data->sema_write = sem_open(SEMA_WRITE, O_CREAT | O_EXCL, 0660, 1);
	if (data->sema_write == SEM_FAILED)
		return (abort_semaphore_init(data));
	data->sema_search = sem_open(SEMA_SEARCH, O_CREAT | O_EXCL, 0660, 1);
	if (data->sema_search == SEM_FAILED)
		return (abort_semaphore_init(data));
	return (OK);
}
