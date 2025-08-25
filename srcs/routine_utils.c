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

bool	should_stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->stop_sim_mutex);
	if (philo->to_stop_simulation == true)
		return (pthread_mutex_unlock(&philo->stop_sim_mutex), true);
	pthread_mutex_unlock(&philo->stop_sim_mutex);
	return (false);
}

int	stop_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->stop_sim_mutex);
	philo->to_stop_simulation = true;
	pthread_mutex_unlock(&philo->stop_sim_mutex);
	return (EXIT_SUCCESS);
}

unsigned long	get_elapsed_time(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec * 1000000 + end->tv_usec)
		- (start->tv_sec * 1000000 + start->tv_usec));
}

int	get_current_time(struct timeval *current_time)
{
	if (gettimeofday(current_time, NULL) < 0)
		return (error_msg(TIME_ERROR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	print_status(t_philo *philo, int id, char *str)
{
	struct timeval	current_time;
	unsigned long	time_elapsed;

	pthread_mutex_lock(&philo->print_mutex);
	if (get_current_time(&current_time) == EXIT_FAILURE)
		return (stop_simulation(philo), EXIT_FAILURE);
	time_elapsed = get_elapsed_time(&philo->start_time, &current_time);
	printf("%ldms philo %d %s", time_elapsed, id + 1, str);
	pthread_mutex_unlock(&philo->print_mutex);
	return (EXIT_SUCCESS);
}
