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
#include <stdio.h>
#include <sys/time.h>

static int	routine_sleep(t_philo *philo)
{
	print_status(philo, philo->philo_id, SLEEP);
	segments_usleep(philo, philo->prog_data->time_to_sleep);
	return (EXIT_SUCCESS);
}

static int	routine_think(t_philo *philo)
{
	print_status(philo, philo->philo_id, THINK);
	return (EXIT_SUCCESS);
}

/**
 * @brief The fucntion of thread.
 *
 * @param philos The philos structure.
 * @return SUCCESS or FAILURE.
 */
static void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (should_stop_simulation(philo) == false)
			routine_eat(philo);
		if (should_stop_simulation(philo) == false)
			routine_sleep(philo);
		if (should_stop_simulation(philo) == false)
			routine_think(philo);
		if (should_stop_simulation(philo) == true)
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
int	start_routine(t_philo *philo, t_params *prog_data)
{
	int	n;
	int	ret;

	n = 0;
	while (n < prog_data->philo_num)
	{
		ret = pthread_create(&philo[n].thread_id, NULL,
				thread_routine, (void *)&philo[n]);
		if (ret < 0)
			return (error_msg(THREAD_ERROR_CREAT), EXIT_FAILURE);
		n++;
	}
	return (EXIT_SUCCESS);
}
