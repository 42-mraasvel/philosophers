/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/05 20:34:57 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/13 09:23:35 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "proto.h"

/*
Input is sanitized by converting to string and back
*/

static int	parse_arg(int *dst, char *src)
{
	int		n;
	char	*temp;

	n = ft_atoi(src);
	if (n < 0)
		return (ft_error("Input", src));
	temp = ft_itoa(n);
	if (temp == NULL)
		return (ft_perror("malloc"));
	if (ft_strcmp(temp, src) != 0)
	{
		free(temp);
		return (ft_error("Input", src));
	}
	free(temp);
	*dst = n;
	return (OK);
}

/*
Errors:
	- Argument count is not 5 or 6
	- Not a valid number string
	- Number of philosophers is <= 1 (1 philosopher would have only 1 fork)
*/

int	get_input(t_input *input, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (ft_error("Input", "invalid argument count"));
	if (parse_arg(&input->num_philo, argv[1]))
		return (ERR);
	if (parse_arg(&input->time_to_die, argv[2]))
		return (ERR);
	if (parse_arg(&input->time_to_eat, argv[3]))
		return (ERR);
	if (parse_arg(&input->time_to_sleep, argv[4]))
		return (ERR);
	if (argc == 6)
		if (parse_arg(&input->num_times_to_eat, argv[5]) == ERR)
			return (ERR);
	if (input->num_philo <= 0)
		return (ft_error("Input: number_of_philosophers: invalid value",
				argv[1]));
	return (OK);
}
