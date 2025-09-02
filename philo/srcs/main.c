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
#include <stdio.h>

int	terminate_threads(t_params *prog_data, t_philo *philo)
{
	int			n_threads;

	n_threads = 0;
	while (n_threads < prog_data->philo_num)
	{
		if (philo[n_threads].thread_id != 0)
			pthread_join(philo[n_threads].thread_id, NULL);
		n_threads++;
	}
	pthread_join(prog_data->monitoring_thread_id, NULL);
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
	usleep(1000);
	start_global_monitoring_thread(philo, &param);
	terminate_threads(&param, philo);
	clean_data(&philo, &param);
	return (EXIT_SUCCESS);
}
