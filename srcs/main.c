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
	t_philo		*philo;
	t_params	param;

	philo = NULL;
	if (is_valid_args(argc, &argv[1]) == false)
		return (error_msg(ARGS_ERROR), EXIT_FAILURE);
	if (init_params_and_philos(&philo, &param, &argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_routine(philo, &param) == EXIT_FAILURE)
		return (clean_data(&philo, &param), EXIT_FAILURE);
	start_global_monitoring_thread(&param, philo);
	terminate_threads(&param, philo);
	clean_data(&philo, &param);
	return (EXIT_SUCCESS);
}
