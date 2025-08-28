/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizhouis <mizhouis@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:32:51 by mizhouis          #+#    #+#             */
/*   Updated: 2025/08/21 17:32:56 by mizhouis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_philos(t_philo **philo, t_params *prog_data)
{
	int	n;

	n = 0;
	*philo = malloc(prog_data->philo_num * sizeof(t_philo));
	if (*philo == NULL)
		return (EXIT_FAILURE);
	while (n < prog_data->philo_num)
	{
		(*philo)[n].philo_id = n;
		(*philo)[n].thread_id = 0;
		(*philo)[n].times_eaten = 0;
		(*philo)[n].prog_data = prog_data;
		if (pthread_mutex_init(&(*philo)[n].fork_mutex, NULL) < 0)
			return (destroy_mutex_in_n_structure(*philo, n), free(*philo),
				*philo = NULL, EXIT_FAILURE);
		if (pthread_mutex_init(
				&(*philo)[n].last_meal_time_and_times_eaten_mutex,
			NULL) < 0)
			return (destroy_mutex_in_n_structure(*philo, n),
				pthread_mutex_destroy(&(*philo)[n].fork_mutex), free(*philo),
					*philo = NULL, EXIT_FAILURE);
		n++;
	}
	return (EXIT_SUCCESS);
}

static int	init_params(t_params *prog_data, char **arg)
{
	prog_data->philo_num = (int)ft_atol(arg[0]);
	if (prog_data->philo_num == 0)
		return (error_msg(ARGS_ERROR_NOPHILO), EXIT_FAILURE);
	prog_data->time_to_die = (unsigned int)ft_atol(arg[1]);
	printf("time to die %d\n", (unsigned int)prog_data->time_to_die);
	prog_data->time_to_eat = (unsigned int)ft_atol(arg[2]);
	printf("time to eat %d\n", (unsigned int)prog_data->time_to_eat);
	prog_data->time_to_sleep = (unsigned int)ft_atol(arg[3]);
	printf("time to sleep %d\n", (unsigned int)prog_data->time_to_sleep);
	if (arg[4])
		prog_data->times_must_eat = (int)ft_atol(arg[4]);
	else
		prog_data->times_must_eat = -1;
	printf("time must eat %d\n", prog_data->times_must_eat);
	if (gettimeofday(&prog_data->start_time, NULL) < 0)
		return (error_msg(TIME_ERROR), EXIT_FAILURE);
	if (pthread_mutex_init(&prog_data->print_mutex, NULL) < 0)
		return (EXIT_FAILURE);
	prog_data->to_stop_simulation = false;
	if (pthread_mutex_init(&prog_data->stop_sim_mutex, NULL) < 0)
		return (pthread_mutex_destroy(&prog_data->print_mutex), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_params_and_philos(t_philo **philo, t_params *prog_data, char **arg)
{
	if (init_params(prog_data, arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(philo, prog_data) == EXIT_FAILURE)
		return (pthread_mutex_destroy(&prog_data->print_mutex),
			pthread_mutex_destroy(&prog_data->stop_sim_mutex), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
