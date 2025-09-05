/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizhouis <mizhouis@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:44:29 by mizhouis          #+#    #+#             */
/*   Updated: 2025/08/23 16:44:29 by mizhouis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	segments_usleep(t_philo *philo, unsigned int time)
{
	struct timeval	start_time;
	struct timeval	current_time;

	gettimeofday(&start_time, NULL);
	while (should_stop_simulation(philo) == false)
	{
		usleep(TIME_INTERVAL_CHECK_IF_STOP_SIM_US);
		gettimeofday(&current_time, NULL);
		if (get_time_elapsed_ms(&start_time, &current_time) >= time)
			break ;
	}
	return (EXIT_SUCCESS);
}

bool	should_stop_simulation(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->prog_data->stop_sim_mutex);
	ret = philo->prog_data->to_stop_simulation;
	pthread_mutex_unlock(&philo->prog_data->stop_sim_mutex);
	return (ret);
}

int	stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->prog_data->stop_sim_mutex);
	philo->prog_data->to_stop_simulation = true;
	pthread_mutex_unlock(&philo->prog_data->stop_sim_mutex);
	return (EXIT_SUCCESS);
}

bool	is_even(int num)
{
	if (num % 2 == 0)
		return (true);
	return (false);
}

int	print_status(t_philo *philo, int id, char *str)
{
	long long int	time_stamps_ms;

	if (should_stop_simulation(philo) == false)
	{
		pthread_mutex_lock(&philo->prog_data->print_mutex);
		if (get_time_stamps_ms(&time_stamps_ms) == EXIT_FAILURE)
			return (stop_simulation(philo), EXIT_FAILURE);
		printf("%lld %d %s", time_stamps_ms, id, str);
		pthread_mutex_unlock(&philo->prog_data->print_mutex);
	}
	return (EXIT_SUCCESS);
}
