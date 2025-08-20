/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:47:02 by mzhou             #+#    #+#             */
/*   Updated: 2025/08/20 16:47:32 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/** get lenth of a string.
* @param str: the string
* @return lenth of the string
*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/** get lenth of a string.
* @param str: the string
* @return lenth of the string
*/
int	error_quit(char *msg)
{
	int	size;

	size = ft_strlen(msg);
	write(2, msg, size);
	return (EXIT_SUCCESS);
}
