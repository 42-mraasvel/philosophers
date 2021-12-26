/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   proto.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/26 11:39:49 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/14 17:47:23 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTO_H
# define PROTO_H

# include "philo.h"

/* Philosophers / Children / Forks */

int				create_children(t_data *data);
int				forked_routine(t_data *data);
void			monitor_children(t_data *data);
void			*philo_routine(void *data_ptr);
int				process_init(t_data *data);

void			print_msg(t_data *data, enum e_msg msg);
int				get_input(t_input *input, int argc, char *argv[]);

/* Semaphores */

int				semaphore_init(t_data *data);
void			semaphores_destroy(t_data *data);
void			semaphore_destroy(sem_t *semaphore, char *name);

/* Time Functions */

void			ms_sleep(long microseconds);
long			elapsed_time(struct timeval start);
struct timeval	get_time(void);
void			philo_wait(t_data *data, long time_to_wait);

/* Utillity Functions */

int				ft_atoi(char *s);;
char			*ft_itoa(int n);
int				ft_perror(char *s);
int				ft_error(char *a, char *b);
int				ft_strcmp(char *a, char *b);
void			ft_bzero(void *dst, size_t size);
int				ft_putstr_fd(int fd, char *str);

#endif
