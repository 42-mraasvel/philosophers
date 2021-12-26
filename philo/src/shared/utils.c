/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/31 16:52:34 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/08 14:48:05 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "proto.h"

void	ft_swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_bzero(void *dst, size_t size)
{
	unsigned char	*d;

	d = dst;
	while (size > 0)
	{
		*d = 0;
		d++;
		size--;
	}
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (a[i] != b[i])
			return ((unsigned char)a[i] - (unsigned char)b[i]);
		i++;
	}
	return (0);
}

/*
Write custom message to STDERR
Return ERR
*/

int	ft_error(char *a, char *b)
{
	ft_putstr_fd(STDERR_FILENO, "Error: ");
	if (a)
		ft_putstr_fd(STDERR_FILENO, a);
	if (b)
	{
		ft_putstr_fd(STDERR_FILENO, ": ");
		ft_putstr_fd(STDERR_FILENO, b);
	}
	ft_putstr_fd(STDERR_FILENO, "\n");
	return (ERR);
}

int	ft_perror(char *s)
{
	perror(s);
	return (ERR);
}
