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
#include <stdbool.h>
#include <stdlib.h>

bool	is_int(char *str)
{
	
}

bool	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (error_quit(ARGS_ERROR), false);
	while (argv[i])
	{
		if (is_int(argv[i]) == false)
			return (error_quit(ARGS_ERROR), false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo		philos;

	if (is_valid_args(argc, argv) == false)
		exit (EXIT_FAILURE);
	init_philos(&philos, argc, argv);
	routine(&philos);
	return (EXIT_SUCCESS);
}
