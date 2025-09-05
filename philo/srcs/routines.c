/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizhouis <mizhouis@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:31:28 by mizhouis          #+#    #+#             */
/*   Updated: 2025/08/22 10:31:28 by mizhouis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	routine_sleep(t_philo *philo)
{
	print_status(philo, philo->philo_id, SLEEP);
	segments_usleep(philo, philo->prog_data->time_to_sleep);
	return (EXIT_SUCCESS);
}

int	routine_think(t_philo *philo)
{
	long int	time_to_think;

	time_to_think = philo->prog_data->time_to_eat * 2
		- philo->prog_data->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	print_status(philo, philo->philo_id, THINK);
	// if (is_even(philo->prog_data->philo_num) == false && time_to_think > 0)
	// 	segments_usleep(philo, (unsigned int)time_to_think * 0.4);
	return (EXIT_SUCCESS);
}

int	routine_eat(t_philo *philo)
{
	if (philo->prog_data->philo_num == 1)
		one_philo_eat(philo);
	else
	{
		if (get_two_forks(philo, philo->philo_id) == EXIT_SUCCESS)
		{
			print_status(philo, philo->philo_id, EAT);
			update_last_meal_time_and_times_eaten(philo);
			segments_usleep(philo, philo->prog_data->time_to_eat);
			if (drop_two_forks(philo, philo->philo_id) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
		}
	}
	stop_simulation(philo);
	return (EXIT_FAILURE);
}
