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
#include <unistd.h>

static int	routine_sleep(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("philo[%d] begin to sleep\n", id);
	pthread_mutex_unlock(&philo->print_mutex);
	sleep(philo->time_to_sleep);
	return (EXIT_SUCCESS);
}

static int	routine_think(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->print_mutex);
	printf("philo[%d] begin to think\n", id);
	pthread_mutex_unlock(&philo->print_mutex);
	return (EXIT_SUCCESS);
}

static int	pick_fork(t_philo *philo, int id_fork)
{
	while (1)
	{
		if (philo->forks[id_fork - 1] == FREE_TO_USE)
			break ;
	}
	pthread_mutex_lock(&philo->fork_mutex[id_fork - 1]);
	printf("philo[%d] take a fork\n", id);
	pthread_mutex_unlock(&philo->print_mutex);
	return (EXIT_SUCCESS);

}

static int	routine_eat(t_philo *philo, int id)
{
	if (id == philo->philo_num - 1)
	{
		pick_fork(philo, id - 1);
		pick_fork(philo, id);
	}
	else
	{
		pick_fork(philo, id);
		pick_fork(philo, id - 1);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief The fucntion of thread.
 *
 * @param philos The philos structure.
 * @return SUCCESS or FAILURE.
 */
static void	*thread_routine(void *philo)
{
	int	id;

	pthread_mutex_lock(&(((t_philo *)philo)->id_mutex));
	((t_philo *)philo)->philo_id++;
	id = ((t_philo *)philo)->philo_id;
	pthread_mutex_unlock(&(((t_philo *)philo)->id_mutex));
	printf("my id is philo %d\n", id);
	routine_eat(philo, id);
	routine_sleep(philo, id);
	routine_think(philo, id);
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
		ret = pthread_create(&philos->thread_ids[n], NULL,
				thread_routine, (void *)philos);
		if (ret < 0)
			return (error_msg(THREAD_ERROR_CREAT), EXIT_FAILURE);
		n++;
	}
	return (EXIT_SUCCESS);
}
