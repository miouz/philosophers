/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:21:13 by mzhou             #+#    #+#             */
/*   Updated: 2025/09/02 11:21:54 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	update_last_meal_time_and_times_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_time_and_times_eaten_mutex);
	gettimeofday(&philo->last_meal_time, NULL);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->last_meal_time_and_times_eaten_mutex);
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
