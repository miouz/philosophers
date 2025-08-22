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
#include <stdlib.h>
#include <string.h>

int	init_philos(t_philo *philo, char **arg)
{
	memset(philo, 0, sizeof(t_philo));
	philo->to_stop_simulation = false;
	philo->philo_num = (int)ft_atol(arg[0]);
	philo->time_to_die = (int)ft_atol(arg[1]);
	philo->time_to_eat = (int)ft_atol(arg[2]);
	philo->time_to_sleep = (int)ft_atol(arg[3]);
	if (arg[4])
		philo->times_must_eat = (int)ft_atol(arg[4]);
	else
		philo->times_must_eat = -1;
	if (philo->philo_num == 0)
		return (error_msg(ARGS_ERROR_NOPHILO), EXIT_FAILURE);
	philo->status = malloc(philo->philo_num * sizeof(int));
	philo->forks = malloc(philo->philo_num * sizeof(int));
	philo->mutex = malloc(philo->philo_num * sizeof(pthread_mutex_t));
	philo->thread_ids = malloc(philo->philo_num * sizeof(pthread_t));
	if (!philo->forks || !philo->status || !philo->mutex || !philo->thread_ids)
		return (free(philo->status), free(philo->forks), free(philo->mutex),
			free(philo->thread_ids), error_msg(MALLOC_ERROR), EXIT_FAILURE);
	memset(philo->status, 0, philo->philo_num);
	memset(philo->forks, 0, philo->philo_num);
	return (EXIT_SUCCESS);
}
