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

int	ft_atoi(char *str)
{
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
int	error_quit(char *msg)
{
	int	size;

	size = ft_strlen(msg);
	write(2, msg, size);
	return (EXIT_SUCCESS);
}
