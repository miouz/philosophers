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

static int	init_philos(t_philo **philo, t_params *prog_data, int struct_index)
{
	*philo = malloc(prog_data->philo_num * sizeof(t_philo));
	if (*philo == NULL)
		return (error_msg(ERROR_MALLOC), EXIT_FAILURE);
	while (struct_index < prog_data->philo_num)
	{
		(*philo)[struct_index].philo_id = struct_index + 1;
		(*philo)[struct_index].thread_id = 0;
		(*philo)[struct_index].times_eaten = -1;
		(*philo)[struct_index].prog_data = prog_data;
		if (pthread_mutex_init(&(*philo)[struct_index].fork_mutex, NULL) < 0)
			return (destroy_mutex_in_n_structure(*philo, struct_index),
				free(*philo), *philo = NULL, error_msg(ERROR_MUTEX),
				EXIT_FAILURE);
		if (pthread_mutex_init(
				&(*philo)[struct_index].last_meal_time_and_times_eaten_mutex,
			NULL) < 0)
			return (destroy_mutex_in_n_structure(*philo, struct_index),
				pthread_mutex_destroy(&(*philo)[struct_index].fork_mutex),
				free(*philo), *philo = NULL, error_msg(ERROR_MUTEX),
				EXIT_FAILURE);
		struct_index++;
	}
	return (EXIT_SUCCESS);
}

static int	init_params(t_params *prog_data, char **arg)
{
	prog_data->philo_num = (int)ft_atol(arg[0]);
	if (prog_data->philo_num == 0)
		return (error_msg(ERROR_ARGS_NOPHILO), EXIT_FAILURE);
	prog_data->time_to_die = (unsigned int)ft_atol(arg[1]);
	prog_data->time_to_eat = (unsigned int)ft_atol(arg[2]);
	prog_data->time_to_sleep = (unsigned int)ft_atol(arg[3]);
	if (arg[4])
		prog_data->times_must_eat = (int)ft_atol(arg[4]);
	else
		prog_data->times_must_eat = -1;
	if (!prog_data->time_to_die || !prog_data->times_must_eat)
		return (error_msg(ERROR_ARGS_ZERO), EXIT_FAILURE);
	if (pthread_mutex_init(&prog_data->print_mutex, NULL) < 0)
		return (error_msg(ERROR_MUTEX), EXIT_FAILURE);
	prog_data->to_stop_simulation = false;
	if (pthread_mutex_init(&prog_data->stop_sim_mutex, NULL) < 0)
		return (error_msg(ERROR_MUTEX),
			pthread_mutex_destroy(&prog_data->stop_sim_mutex), EXIT_FAILURE);
	prog_data->begin_to_eat = false;
	if (pthread_mutex_init(&prog_data->begin_to_eat_mutex, NULL) < 0)
		return (error_msg(ERROR_MUTEX),
			pthread_mutex_destroy(&prog_data->begin_to_eat_mutex),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_params_and_philos(t_philo **philo, t_params *prog_data, char **arg)
{
	if (init_params(prog_data, arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos(philo, prog_data, 0) == EXIT_FAILURE)
		return (pthread_mutex_destroy(&prog_data->print_mutex),
			pthread_mutex_destroy(&prog_data->stop_sim_mutex), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
