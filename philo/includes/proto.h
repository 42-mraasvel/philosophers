/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:16:27 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include <stddef.h>
# include "philo.h"

/* Other Functions */

int				get_input(t_input *input, int argc, char *argv[]);
void			print_msg(t_philo *philo, enum e_msg msg);

/* Philo Routine Functions */

void			*philo_routine(void *philo_ptr);
void			*monitor_routine(void *philo_ref);

int				right_index(t_philo *philo);
int				left_index(t_philo *philo);

/* Thread Functions */

void			monitor_threads(t_data *data);
int				create_threads(t_data *data);
int				join_threads(t_data *data);

/* Mutex Functions */

int				mutex_init(t_data *data);
void			mutex_destroy(t_data *data);

/* Time Functions */

void			ms_sleep(long ms, t_philo *philo);
void			philo_wait(t_philo *philo, long ms);
long			elapsed_time(struct timeval start);
struct timeval	get_time(void);

/* Utillity Functions */

int				ft_atoi(char *s);
char			*ft_itoa(int n);
void			ft_bzero(void *dst, size_t size);
int				ft_strcmp(char *a, char *b);
int				ft_error(char *a, char *b);
int				ft_perror(char *s);
void			ft_swap_int(int *a, int *b);
int				ft_putstr_fd(int fd, char *str);

#endif
