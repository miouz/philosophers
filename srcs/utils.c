/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizhouis <mizhouis@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:59:29 by mizhouis          #+#    #+#             */
/*   Updated: 2025/08/20 20:59:29 by mizhouis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file utils.c
 * @brief utils helper function
 */

#include "../includes/philo.h"

void	free_philos(t_philo *philos)
{
	free(philos->forks);
	free(philos->status);
	free(philos->mutex);
}

long int	ft_atol(const char *nptr)
{
	long int	nbr;
	int			i;
	int			p_or_n;

	nbr = 0;
	i = 0;
	p_or_n = 1;
	while (((nptr[i] >= 9) && (nptr[i] <= 13)) || nptr[i] == 32)
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			p_or_n = -1;
		i++;
	}
	while ((nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbr * p_or_n);
}

/**
 * @brief get string length.
 * @param str string.
 * @return length.
 */
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
* @brief print error message on stderr.
* @param msg: error message to print.
* @return EXIT_SUCCESS or EXIT_FAILURE.
*/
int	error_msg(char *msg)
{
	int	size;

	size = ft_strlen(msg);
	write(2, msg, size);
	return (EXIT_SUCCESS);
}
