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

static int	drop_fork(pthread_mutex_t *fork_mutex)
{
	int	return_value;

	return_value = EXIT_FAILURE;
	while (1)
	{
		return_value = pthread_mutex_unlock(fork_mutex);
		if (return_value == EXIT_SUCCESS)
			break ;
	}
	return (EXIT_SUCCESS);
}

static int	pick_fork(t_philo *philo, pthread_mutex_t *fork_mutex, int id_philo)
{
	int	return_value;

	return_value = EXIT_FAILURE;
	while (1)
	{
		return_value = pthread_mutex_lock(fork_mutex);
		if (return_value == EXIT_SUCCESS)
			break ;
	}
	print_status(philo, id_philo, "has taken a fork\n");
	return (EXIT_SUCCESS);
}

int	drop_two_forks(t_philo *philo, int id)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork_mutex;
	if (id == 1)
		right_fork = &(philo + (philo->prog_data->philo_num - 1))->fork_mutex;
	else
		right_fork = &(philo - 1)->fork_mutex;
	if (is_even(id) == false)
	{
		if (drop_fork(left_fork) == EXIT_SUCCESS
			&& drop_fork(right_fork) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	else
	{
		if (drop_fork(right_fork) == EXIT_SUCCESS
			&& drop_fork(left_fork) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * @brief Get two forks in right order.
 * Philo_num is odd:
 * odd philo_id eat first, even philo_id eat after.
 * odd philo_id get left_fork first, even philo_id get right_fork firstly.
 * philo_num is even:
 * odd philo_id eat first, even philo_id eat after.
 * odd philo_id get left_fork first, even philo_id get right_fork firstly.
 * @param philo philo's structure
 * @param id philo's own id from 1 to philo_num
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int	get_two_forks(t_philo *philo, int id)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork_mutex;
	if (id == 1)
		right_fork = &(philo + (philo->prog_data->philo_num - 1))->fork_mutex;
	else
		right_fork = &(philo - 1)->fork_mutex;
	if (is_even(id) == false)
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

void	one_philo_eat(t_philo *philo)
{
	pick_fork(philo, &philo->fork_mutex, philo->philo_id);
	drop_fork(&philo->fork_mutex);
	segments_usleep(philo, philo->prog_data->time_to_die * 2);
}
