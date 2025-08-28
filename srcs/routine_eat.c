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

static int	drop_fork(t_philo *philo, pthread_mutex_t *fork_mutex, int id_philo)
{
	int	retval;

	retval = EXIT_FAILURE;
	while (1)
	{
		retval = pthread_mutex_unlock(fork_mutex);
		if (retval == EXIT_SUCCESS)
			break ;
	}
	print_status(philo, id_philo, "has drop a fork\n");
	return (EXIT_SUCCESS);
}

static int	pick_fork(t_philo *philo, pthread_mutex_t *fork_mutex, int id_philo)
{
	int	retval;

	retval = EXIT_FAILURE;
	while (1)
	{
		retval = pthread_mutex_lock(fork_mutex);
		if (retval == EXIT_SUCCESS)
			break ;
	}
	print_status(philo, id_philo, "has taken a fork\n");
	return (EXIT_SUCCESS);
}

static int	drop_two_forks(t_philo *philo, int id)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork_mutex;
	if (id == 0)
		right_fork = &(philo + (philo->prog_data->philo_num - 1))->fork_mutex;
	else
		right_fork = &(philo - 1)->fork_mutex;
	if (id == philo->prog_data->philo_num - 1)
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork_mutex;
	if (id == 0)
		right_fork = &(philo + (philo->prog_data->philo_num - 1))->fork_mutex;
	else
		right_fork = &(philo - 1)->fork_mutex;
	if (id == philo->prog_data->philo_num - 1)
	{
		if (pick_fork(philo, left_fork, id) == EXIT_SUCCESS
			&& should_stop_simulation(philo) == false
			&& pick_fork(philo, right_fork, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	else
	{
		if (pick_fork(philo, right_fork, id) == EXIT_SUCCESS
			&& should_stop_simulation(philo) == false
			&& pick_fork(philo, left_fork, id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int	update_last_meal_time_and_times_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_time_and_times_eaten_mutex);
	gettimeofday(&philo->last_meal_time, NULL);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->last_meal_time_and_times_eaten_mutex);
	return (EXIT_SUCCESS);
}

int	routine_eat(t_philo *philo)
{
	if (get_two_forks(philo, philo->philo_id) == EXIT_SUCCESS)
	{
		print_status(philo, philo->philo_id, EAT);
		update_last_meal_time_and_times_eaten(philo);
		segments_usleep(philo, philo->prog_data->time_to_eat);
		if (drop_two_forks(philo, philo->philo_id) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	stop_simulation(philo);
	return (EXIT_FAILURE);
}
