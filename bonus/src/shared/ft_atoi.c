/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mraasvel <mraasvel@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/01 10:30:39 by mraasvel      #+#    #+#                 */
/*   Updated: 2021/06/08 08:28:48 by mraasvel      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *s)
{
	int	negative;
	int	n;

	while (ft_isspace(*s))
		s++;
	negative = (*s == '-');
	if (*s == '+' || *s == '-')
		s++;
	n = 0;
	while (ft_isdigit(*s))
	{
		n = (n * 10) + (*s - '0');
		s++;
	}
	if (negative)
		return (-n);
	return (n);
}
