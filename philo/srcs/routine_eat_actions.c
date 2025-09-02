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
#include <stdbool.h>

static int	drop_fork(pthread_mutex_t *fork_mutex)
{
	int	retval;

	retval = EXIT_FAILURE;
	while (1)
	{
		retval = pthread_mutex_unlock(fork_mutex);
		if (retval == EXIT_SUCCESS)
			break ;
	}
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

int	drop_two_forks(t_philo *philo, int id)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork_mutex;
	if (id == 0)
		right_fork = &(philo + (philo->prog_data->philo_num - 1))->fork_mutex;
	else
		right_fork = &(philo - 1)->fork_mutex;
	if (is_even(id) == true)
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

int	get_two_forks(t_philo *philo, int id)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork_mutex;
	if (id == 0)
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
