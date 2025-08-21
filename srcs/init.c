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
#include <string.h>

int	init_philos(t_philo *philo, char **arg)
{
	philo->status = NULL;
	philo->forks = NULL;
	philo->mutex = NULL;
	philo->philo_num = (int)ft_atol(arg[0]);
	philo->time_to_die = (int)ft_atol(arg[1]);
	philo->time_to_eat = (int)ft_atol(arg[2]);
	philo->time_to_sleep = (int)ft_atol(arg[3]);
	if (arg[4])
		philo->times_must_eat = (int)ft_atol(arg[4]);
	else
		philo->times_must_eat = -1;
	if (philo->philo_num == 0)
		return (error_quit(ARGS_ERROR_NOPHILO), EXIT_FAILURE);
	philo->status = malloc(philo->philo_num * sizeof(int));
	philo->forks = malloc(philo->philo_num * sizeof(int));
	philo->mutex = malloc(philo->philo_num * sizeof(int));
	if (!philo->forks || !philo->status || !philo->mutex)
		return (free(philo->status), free(philo->forks),
			free(philo->mutex), error_quit(MALLOC_ERROR), EXIT_FAILURE);
	memset(philo->status, 0, philo->philo_num);
	memset(philo->forks, 0, philo->philo_num);
	memset(philo->mutex, 0, philo->philo_num);
	return (EXIT_SUCCESS);
}
