/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizhouis <mizhouis@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:31:28 by mizhouis          #+#    #+#             */
/*   Updated: 2025/08/22 10:31:28 by mizhouis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

static int	routine_sleep(t_philo *philo, int id)
{
	(void)id;
	print_status(philo, id, SLEEP);
	usleep(philo->time_to_sleep);
	return (EXIT_SUCCESS);
}

static int	routine_think(t_philo *philo, int id)
{
	(void)philo;
	(void)id;
	print_status(philo, id, THINK);
	return (EXIT_SUCCESS);
}

static int	get_philo_id(t_philo *philo)
{
	int	id;

	pthread_mutex_lock(&philo->id_mutex);
	id = philo->philo_id;
	philo->philo_id++;
	pthread_mutex_unlock(&philo->id_mutex);
	return (id);
}

/**
 * @brief The fucntion of thread.
 *
 * @param philos The philos structure.
 * @return SUCCESS or FAILURE.
 */
static void	*thread_routine(void *arg)
{
	int		id;
	t_philo	*philo;

	philo = (t_philo *)arg;
	id = get_philo_id(philo);
	while (1)
	{
		if (should_stop_simulation(philo) == false)
			routine_eat(philo, id);
		if (should_stop_simulation(philo) == false)
			routine_sleep(philo, id);
		if (should_stop_simulation(philo) == false)
			routine_think(philo, id);
		else
			break ;
	}
	return (NULL);
}

/**
 * @brief Prepare and start the philos' routine.
 *
 * @param Philos structure philos.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 * This function:
 * 	-Initialize time.
 * 	-Creat threads with number of philos.
 * 	-Return a value when need to stop simulation.
 */
int	start_routine(t_philo *philo)
{
	int	n;
	int	ret;

	if (gettimeofday(&philo->start_time, NULL) != EXIT_SUCCESS)
		return (error_msg(TIME_ERROR), EXIT_FAILURE);
	n = 0;
	while (n < philo->philo_num)
	{
		ret = pthread_create(&philo->thread_ids[n], NULL,
				thread_routine, (void *)philo);
		if (ret < 0)
			return (error_msg(THREAD_ERROR_CREAT), EXIT_FAILURE);
		n++;
	}
	return (EXIT_SUCCESS);
}
