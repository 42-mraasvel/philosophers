/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 18:28:51 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef OK
#  define OK 0
# endif

# ifndef ERR
#  define ERR -1
# endif

# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

enum e_msg
{
	e_grab_fork,
	e_eating,
	e_sleeping,
	e_thinking,
	e_died
};

enum e_status
{
	active,
	inactive,
	joined
};

/*
./philo CLI Arguments:
	num_philo
	time_to_die
	time_to_eat
	time_to_sleep
	[num_times_to_eat]
*/

typedef struct s_input
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_input;

/*
Locks:
	1 for writing
	1 for each fork (num_philo)
	1 extra for each philosopher (num_philo, search lock)
*/

typedef struct s_philo
{
	t_data			*data;
	struct timeval	last_eaten;
	int				times_eaten;
	pthread_mutex_t	search_lock;
	pthread_mutex_t	death_lock;
	int				id;
	enum e_status	status;
	pthread_t		monitor;
}	t_philo;

typedef struct s_data
{
	t_input			input;
	t_philo			*philos;
	struct timeval	start_time;
	pthread_t		*pthreads;
	pthread_mutex_t	*fork_locks;
	pthread_mutex_t	write_lock;
	int				philo_died;
	int				started;
}	t_data;

#endif
