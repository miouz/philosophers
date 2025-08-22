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
#include <stdlib.h>
#include <sys/time.h>

/**
 * @brief The fucntion of thread.
 *
 * @param philos The philos structure.
 * @return SUCCESS or FAILURE.
 */
static void	*thread_routine(void *philos)
{
	printf("my id is philo %d\n", ((t_philo *)philos)->philo_id);
	// routine_eat(philos);
	// routine_sleep(philos);
	// routine_think(philos);
	return (EXIT_SUCCESS);
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
int	start_routine(t_philo *philos)
{
	int	n;
	int	ret;

	if (gettimeofday(&philos->time, NULL) != EXIT_SUCCESS)
		return (error_msg(TIME_ERROR), EXIT_FAILURE);
	n = 0;
	while (n < philos->philo_num)
	{
		philos->philo_id = n + 1;
		ret = pthread_create(&philos->thread_ids[n], NULL,
				thread_routine, (void *)philos);
		if (ret < 0)
			return (error_msg(THREAD_ERROR_CREAT), EXIT_FAILURE);
		n++;
	}
	return (EXIT_SUCCESS);
}
