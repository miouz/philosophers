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
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <stdlib.h>
#include <unistd.h>

int	init_mutex_array(pthread_mutex_t *mutex, int num)
{
	num = num - 1;
	while (num >= 0)
	{
		if (pthread_mutex_init(&mutex[num], NULL) < 0)
			return (EXIT_FAILURE);
		num--;
	}
	return (EXIT_SUCCESS);
}

int	init_monitoring_infos(t_philo *philo, char **arg)
{
	memset(philo, 0, sizeof(t_philo));
	philo->to_stop_simulation = false;
	philo->philo_id = 0;
	philo->philo_num = (int)ft_atol(arg[0]);
	philo->time_to_die = (unsigned int)ft_atol(arg[1]);
	printf("time to die %d\n", (unsigned int)philo->time_to_die);
	philo->time_to_eat = (unsigned int)ft_atol(arg[2]);
	printf("time to eat %d\n", (unsigned int)philo->time_to_eat);
	philo->time_to_sleep = (unsigned int)ft_atol(arg[3]);
	printf("time to sleep %d\n", (unsigned int)philo->time_to_sleep);
	if (arg[4])
		philo->times_must_eat = (int)ft_atol(arg[4]);
	else
		philo->times_must_eat = -1;
	printf("time must eat %d\n", philo->times_must_eat);
	if (philo->philo_num == 0)
		return (error_msg(ARGS_ERROR_NOPHILO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_philos_allocated_infos(t_philo *philo)
{
	philo->times_eaten = malloc(philo->philo_num * sizeof(unsigned int));
	philo->last_meal_time = malloc(philo->philo_num * sizeof(struct timeval));
	philo->last_meal_time_and_times_eaten_mutex = malloc(philo->philo_num * sizeof(pthread_mutex_t));
	philo->fork_mutex = malloc(philo->philo_num * sizeof(pthread_mutex_t));
	philo->thread_ids = malloc((philo->philo_num + 1) * sizeof(pthread_t));
	if (!philo->last_meal_time || !philo->last_meal_time_and_times_eaten_mutex || !philo->fork_mutex || !philo->thread_ids || !philo->times_eaten)
		return (free_allocated_infos(philo), error_msg(MALLOC_ERROR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//to do : handle error in case of init failed: to destroy mutex
int	init_infos_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->id_mutex, NULL);
	pthread_mutex_init(&philo->print_mutex, NULL);
	pthread_mutex_init(&philo->stop_sim_mutex, NULL);
	if (init_mutex_array(philo->fork_mutex, philo->philo_num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mutex_array(philo->last_meal_time_and_times_eaten_mutex, philo->philo_num) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_philos(t_philo *philo, char **arg)
{
	if (init_monitoring_infos(philo, arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philos_allocated_infos(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_infos_mutex(philo) == EXIT_FAILURE)
	{
		free_allocated_infos(philo);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
