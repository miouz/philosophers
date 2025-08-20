/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:21:52 by mzhou             #+#    #+#             */
/*   Updated: 2025/08/19 18:21:52 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 && argc != 6)
		return (error_quit(ARGS_ERROR), 1);
	return (EXIT_SUCCESS);
}
