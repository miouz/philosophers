/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:36:13 by mzhou             #+#    #+#             */
/*   Updated: 2025/08/21 14:36:13 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief check if is valid int.
 *
 * @param str string of argv[i].
 * @return true or false.
 * @detail str should be [numeric] [positif] [in int range].
 */
static bool	is_int(char *str)
{
	long int	num;

	if (is_numeric(str) == true)
	{
		num = ft_atol(str);
		if (num >= 0 && num <= INT_MAX)
			return (true);
	}
	return (false);
}

bool	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (false);
	while (argv[i])
	{
		if (is_int(argv[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
