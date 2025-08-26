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
#include <unistd.h>

int	init_mutex_fork(pthread_mutex_t *mutex, int num)
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

int	init_philos(t_philo *philo, char **arg)
{
	memset(philo, 0, sizeof(t_philo));
	philo->to_stop_simulation = false;
	philo->philo_id = 0;
	philo->philo_num = (int)ft_atol(arg[0]);
	philo->time_to_die = (useconds_t)ft_atol(arg[1]);
	printf("time to die %lu\n", (unsigned long)philo->time_to_die);
	philo->time_to_eat = (useconds_t)ft_atol(arg[2]);
	printf("time to eat %lu\n", (unsigned long)philo->time_to_eat);
	philo->time_to_sleep = (useconds_t)ft_atol(arg[3]);
	printf("time to sleep %lu\n",(unsigned long)philo->time_to_sleep);
	if (arg[4])
		philo->times_must_eat = (useconds_t)ft_atol(arg[4]);
	else
		philo->times_must_eat = -1;
	printf("time must eat %d\n", philo->times_must_eat);
	if (philo->philo_num == 0)
		return (error_msg(ARGS_ERROR_NOPHILO), EXIT_FAILURE);
	philo->status = malloc(philo->philo_num * sizeof(int));
	philo->fork_mutex = malloc(philo->philo_num * sizeof(pthread_mutex_t));
	philo->thread_ids = malloc(philo->philo_num * sizeof(pthread_t));
	if (!philo->status || !philo->fork_mutex || !philo->thread_ids)
		return (free_philos(philo), error_msg(MALLOC_ERROR), EXIT_FAILURE);
	memset(philo->status, 0, philo->philo_num * sizeof(int));
	pthread_mutex_init(&philo->id_mutex, NULL);
	pthread_mutex_init(&philo->print_mutex, NULL);
	pthread_mutex_init(&philo->stop_sim_mutex, NULL);
	if (init_mutex_fork(philo->fork_mutex, philo->philo_num) == EXIT_FAILURE)
		return (free_philos(philo), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
