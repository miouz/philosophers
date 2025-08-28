/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:54:19 by mzhou             #+#    #+#             */
/*   Updated: 2025/08/27 13:54:19 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	annouce_philo_died(t_philo *philo, int index)
{
	print_status(philo, index, DIE);
	stop_simulation(philo);
	return (EXIT_SUCCESS);
}

static unsigned int	get_time_since_last_meal(t_philo *philo,
						int id, struct timeval *current_time)
{
	unsigned int	time_since_last_meal;

	pthread_mutex_lock(&philo->last_meal_time_and_times_eaten_mutex[id]);
	time_since_last_meal = get_time_elapsed_ms(&philo->last_meal_time[id],
			current_time);
	pthread_mutex_unlock(&philo->last_meal_time_and_times_eaten_mutex[id]);
	return (time_since_last_meal);
}

static bool	one_philo_died(t_philo *philo)
{
	struct timeval	current_time;
	unsigned int	time_since_last_meal;
	int				index;

	index = 0;
	gettimeofday(&current_time, NULL);
	while (index < philo->philo_num)
	{
		time_since_last_meal = get_time_since_last_meal(philo, index,
				&current_time);
		if (time_since_last_meal >= philo->time_to_die)
			return (annouce_philo_died(philo, index), true);
		index++;
	}
	return (false);
}

static void	*global_monitoring_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(1000);
		if (one_philo_died(philo) == true)
			return (NULL);
	}
	return (NULL);
}

int	start_global_monitoring_thread(t_philo *philo)
{
	int	ret;

	ret = pthread_create(&philo->thread_ids[philo->philo_num], NULL,
			global_monitoring_thread, (void *)philo);
	if (ret < 0)
		return (error_msg(THREAD_ERROR_CREAT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
