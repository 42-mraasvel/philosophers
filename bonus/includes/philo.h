/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:41:53 by mraasvel      ########   odam.nl         */
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

# define DIED_EXIT_STATUS 1

# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

enum e_msg
{
	e_grab_fork,
	e_eating,
	e_sleeping,
	e_thinking
};

enum e_status
{
	active,
	inactive
};

typedef struct s_input
{
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_input;

typedef struct s_philo
{
	struct timeval	last_eaten;
	int				times_eaten;
	pthread_t		thread;
	enum e_status	status;
	sem_t			*sema_death;
	char			*sema_death_name;
}	t_philo;

typedef struct s_data
{
	t_input			input;
	int				id;
	struct timeval	start_time;
	pid_t			*children;
	sem_t			*sema_write;
	sem_t			*sema_search;
	sem_t			*sema_forks;
	t_philo			*philo;
}	t_data;

#endif
