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

int	terminate_threads(t_philo *philos)
{
	int			n_threads;

	n_threads = 0;
	while (n_threads <= philos->philo_num)
	{
		if (philos->thread_ids[n_threads] != 0)
			pthread_join(philos->thread_ids[n_threads], NULL);
		n_threads++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_philo		philos;

	if (is_valid_args(argc, &argv[1]) == false)
		return (error_msg(ARGS_ERROR), EXIT_FAILURE);
	if (init_philos(&philos, &argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	start_routine(&philos);
	start_global_monitoring_thread(&philos);
	terminate_threads(&philos);
	free_philos(&philos);
	return (EXIT_SUCCESS);
}
