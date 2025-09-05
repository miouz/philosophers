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

static int	annouce_philo_died(t_philo *philo, int id)
{
	print_status(philo, id, DIE);
	stop_simulation(philo);
	return (EXIT_SUCCESS);
}

static bool	one_philo_died_or_full(t_philo *philo, bool *philo_is_full)
{
	struct timeval	current_time;
	unsigned int	time_since_last_meal;
	int				index;

	index = 0;
	gettimeofday(&current_time, NULL);
	while (index < philo->prog_data->philo_num)
	{
		pthread_mutex_lock(&philo[index].last_meal_time_and_times_eaten_mutex);
		time_since_last_meal = get_time_elapsed_ms(&philo[index].last_meal_time,
				&current_time);
		if (philo->prog_data->times_must_eat > -1 && philo[index].times_eaten
			>= philo->prog_data->times_must_eat)
			philo_is_full[index] = true;
		pthread_mutex_unlock(
			&philo[index].last_meal_time_and_times_eaten_mutex);
		if (time_since_last_meal > philo->prog_data->time_to_die)
			return (annouce_philo_died(philo, index + 1), true);
		index++;
	}
	return (false);
}

static bool	all_philos_are_full(bool *philo_is_full, int size, t_philo *philo)
{
	int	n;

	n = 0;
	while (n < size)
	{
		if (philo_is_full[n] == false)
			return (false);
		n++;
	}
	stop_simulation(philo);
	return (true);
}

static void	*global_monitoring_thread(void *arg)
{
	t_philo	*philo;
	bool	*philo_is_full;

	philo = (t_philo *)arg;
	philo_is_full = malloc(philo->prog_data->philo_num * sizeof(bool));
	if (philo_is_full == NULL)
		return (NULL);
	memset(philo_is_full, false, philo->prog_data->philo_num);
	while (1)
	{
		usleep(TIME_DELAY_MONITORING_US);
		if (one_philo_died_or_full(philo, philo_is_full) == true
			|| (philo->prog_data->times_must_eat > -1
				&& all_philos_are_full(philo_is_full,
					philo->prog_data->philo_num, philo) == true))
			return (free(philo_is_full), NULL);
	}
	return (NULL);
}

int	start_global_monitoring_thread(t_philo *philo, t_params *prog_data)
{
	int	ret;

	while (1)
	{
		usleep(TIME_INTERVAL_CHECK_IF_START_MONITORING_US);
		if (should_begin_to_eat(philo) == true)
			break ;
	}
	ret = pthread_create(&prog_data->monitoring_thread_id, NULL,
			global_monitoring_thread, (void *)philo);
	if (ret < 0)
		return (error_msg(ERROR_THREAD), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
