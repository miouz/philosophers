/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizhouis <mizhouis@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 10:22:54 by mizhouis          #+#    #+#             */
/*   Updated: 2025/08/23 10:22:54 by mizhouis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	drop_fork(t_philo *philo, int id_fork, int id_philo)
{
	int	retval;

	retval = EXIT_FAILURE;
	while (1)
	{
		retval = pthread_mutex_unlock(&philo->fork_mutex[id_fork]);
		if (retval == EXIT_SUCCESS)
			break ;
	}
	print_status(philo, id_philo, "has drop a fork\n");
	return (EXIT_SUCCESS);
}

static int	pick_fork(t_philo *philo, int id_fork, int id_philo)
{
	int	retval;

	retval = EXIT_FAILURE;
	while (1)
	{
		retval = pthread_mutex_lock(&philo->fork_mutex[id_fork]);
		if (retval == EXIT_SUCCESS)
			break ;
	}
	print_status(philo, id_philo, "has taken a fork\n");
	return (EXIT_SUCCESS);
}

static int	drop_two_forks(t_philo *philo, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	if (id == 0)
		right_fork = philo->philo_num - 1;
	else
		right_fork = id - 1;
	if (id == philo->philo_num - 1)
	{
		if (drop_fork(philo, left_fork, id) == EXIT_SUCCESS
			&& drop_fork(philo, right_fork, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	else
	{
		if (drop_fork(philo, right_fork, id) == EXIT_SUCCESS
			&& drop_fork(philo, left_fork, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * @brief The eat routine
 * @detail
 * 	-Take one fork
 *	-Take another fork
 *	-Begin to eat
 *	-Drop one fork
 *	-Drop another fork
 * @param philo [The philo structure]
 * @param id Philo's id
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int	get_two_forks(t_philo *philo, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	if (id == 0)
		right_fork = philo->philo_num - 1;
	else
		right_fork = id - 1;
	if (id == philo->philo_num - 1)
	{
		if (pick_fork(philo, left_fork, id) == EXIT_SUCCESS
			&& pick_fork(philo, right_fork, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	else
	{
		if (pick_fork(philo, right_fork, id) == EXIT_SUCCESS
			&& pick_fork(philo, left_fork, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	update_last_meal_time_and_times_eaten(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->last_meal_time_and_times_eaten_mutex[id]);
	gettimeofday(&philo->last_meal_time[id], NULL);
	philo->times_eaten[id]++;
	pthread_mutex_unlock(&philo->last_meal_time_and_times_eaten_mutex[id]);
	return (EXIT_SUCCESS);
}

int	routine_eat(t_philo *philo, int id)
{
	if (get_two_forks(philo, id) == EXIT_SUCCESS)
	{
		print_status(philo, id, EAT);
		update_last_meal_time_and_times_eaten(philo, id);
		usleep(philo->time_to_eat * 1000);
		if (drop_two_forks(philo, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	stop_simulation(philo);
	return (EXIT_FAILURE);
}
