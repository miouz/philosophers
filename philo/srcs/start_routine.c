/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:36:34 by mzhou             #+#    #+#             */
/*   Updated: 2025/09/02 11:36:35 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	should_begin_to_eat(t_philo *philo)
{
	bool	return_value;

	pthread_mutex_lock(&philo->prog_data->begin_to_eat_mutex);
	return_value = philo->prog_data->begin_to_eat;
	pthread_mutex_unlock(&philo->prog_data->begin_to_eat_mutex);
	return (return_value);
}

static int	begin_to_eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->prog_data->begin_to_eat_mutex) < 0)
		return (EXIT_FAILURE);
	philo->prog_data->begin_to_eat = true;
	if (pthread_mutex_unlock(&philo->prog_data->begin_to_eat_mutex) < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Begin to take fork in even philo_num or odd philo_num case.
 * Philo_num is odd:
 * odd philo_id eat first, even philo_id eat after.
 * odd philo_id get left_fork first, even philo_id get right_fork firstly.
 * philo_num is even:
 * odd philo_id eat first, even philo_id eat after.
 * odd philo_id get left_fork first, even philo_id get right_fork firstly.
 * @param philo structure Philo
 */
static void	set_order_for_first_meal_take(t_philo *philo)
{
	if (philo->prog_data->philo_num != 1)
	{
		if (is_even(philo->prog_data->philo_num) == true)
		{
			if (is_even(philo->philo_id) == true)
				segments_usleep(philo, philo->prog_data->time_to_eat * 0.9);
		}
		if (is_even(philo->prog_data->philo_num) == false)
		{
			if (philo->philo_id == philo->prog_data->philo_num)
				segments_usleep(philo, philo->prog_data->time_to_eat * 1.9);
			else if (is_even(philo->philo_id) == true)
				segments_usleep(philo, philo->prog_data->time_to_eat * 0.9);
		}
	}
}

/**
 * @brief The fucntion of thread.
 * -Wait to start simulaitons with all threads simultamnously.
 * -Set meals tean to 0 and last meal time to current time.
 * -Allow philos to take forks for first meal in order .
 * @param philos The philos structure.
 * @return SUCCESS or FAILURE.
 */
static void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(TIME_INTERVAL_CHECK_IF_START_SIM_US);
		if (should_begin_to_eat(philo) == true)
			break ;
	}
	update_last_meal_time_and_times_eaten(philo);
	set_order_for_first_meal_take(philo);
	while (1)
	{
		if (should_stop_simulation(philo) == false)
			routine_eat(philo);
		if (should_stop_simulation(philo) == false)
			routine_sleep(philo);
		if (should_stop_simulation(philo) == false)
			routine_think(philo);
		if (should_stop_simulation(philo) == true)
			break ;
	}
	return (NULL);
}

/**
 * @brief Prepare and start the philos' routine.
 *
 * @param Philos structure philos.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 * This function:
 * 	-Creat threads with number of philos.
 * 	-Allow philos begin the simulation at same time once all thread created.
 */
int	start_routine(t_philo *philo, t_params *prog_data)
{
	int	struct_index;
	int	creat_thread_return;

	struct_index = 0;
	while (struct_index < prog_data->philo_num)
	{
		creat_thread_return = pthread_create(&philo[struct_index].thread_id, 0,
				thread_routine, (void *)&philo[struct_index]);
		if (creat_thread_return < 0)
			return (error_msg(ERROR_THREAD), EXIT_FAILURE);
		struct_index++;
	}
	if (begin_to_eat(philo) == EXIT_FAILURE)
	{
		error_msg(ERROR_EAT);
		stop_simulation(philo);
	}
	return (EXIT_SUCCESS);
}
