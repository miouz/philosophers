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
	t_philo		philos;

	if (is_valid_args(argc, &argv[1]) == false)
		return (error_msg(ARGS_ERROR), EXIT_FAILURE);
	if (init_philos(&philos, &argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_routine(&philos) == EXIT_FAILURE)
		return (free_philos(&philos), EXIT_FAILURE);
	free_philos(&philos);
	return (EXIT_SUCCESS);
}
