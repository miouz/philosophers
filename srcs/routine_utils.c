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
#include <stdlib.h>

int	segments_usleep(t_philo *philo, unsigned int time)
{
	int	n;
	int	rest;

	n = time / 10;
	rest = time % 10;
	while (n > 0 && should_stop_simulation(philo) == false)
	{
		usleep(10 * 1000);
		n--;
	}
	if (rest > 0 && should_stop_simulation(philo) == false)
		usleep(rest * 1000);
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

unsigned int	get_time_elapsed_ms(struct timeval *start, struct timeval *end)
{
	return (((end->tv_sec * 1000000 + end->tv_usec)
			- (start->tv_sec * 1000000 + start->tv_usec)) / 1000);
}

int	get_time_stamps_ms(long long int *time_stamps_ms)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) < 0)
		return (error_msg(TIME_ERROR), EXIT_FAILURE);
	*time_stamps_ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (EXIT_SUCCESS);
}

int	print_status(t_philo *philo, int id, char *str)
{
	long long int	time_stamps_ms;

	if (should_stop_simulation(philo) == false)
	{
		pthread_mutex_lock(&philo->prog_data->print_mutex);
		if (get_time_stamps_ms(&time_stamps_ms) == EXIT_FAILURE)
			return (stop_simulation(philo), EXIT_FAILURE);
		printf("%lldms philo %d %s", time_stamps_ms, id + 1, str);
		pthread_mutex_unlock(&philo->prog_data->print_mutex);
	}
	return (EXIT_SUCCESS);
}
