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
	bool	ret;

	pthread_mutex_lock(&philo->prog_data->begin_to_eat_mutex);
	ret = philo->prog_data->begin_to_eat;
	pthread_mutex_unlock(&philo->prog_data->begin_to_eat_mutex);
	return (ret);
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
 * @brief Begin to take fork if odd or even.
 * Philo_num is even
 * 	philo[even] eat first;
 * philo_num is odd:
 * 	philo[odd] eat first;
 * @param philo structure Philo
 */
static void	set_order_for_first_meal_take(t_philo *philo)
{
	if (philo->prog_data->philo_num != 1)
	{
		if ((is_even(philo->prog_data->philo_num) == true
				&& is_even(philo->philo_id) == false)
			|| ((is_even(philo->prog_data->philo_num) == false)
				&& is_even(philo->philo_id) == true))
			usleep(philo->prog_data->time_to_eat * 800);
	}
}

/**
 * @brief The fucntion of thread.
 *
 * @param philos The philos structure.
 * @return SUCCESS or FAILURE.
 */
static void	*thread_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(200);
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
 * 	-Initialize time.
 * 	-Creat threads with number of philos.
 * 	-Return a value when need to stop simulation.
 */
int	start_routine(t_philo *philo, t_params *prog_data)
{
	int	n;
	int	ret;

	n = 0;
	while (n < prog_data->philo_num)
	{
		ret = pthread_create(&philo[n].thread_id, NULL,
				thread_routine, (void *)&philo[n]);
		if (ret < 0)
			return (error_msg(THREAD_ERROR_CREAT), EXIT_FAILURE);
		n++;
	}
	if (begin_to_eat(philo) == EXIT_FAILURE)
	{
		error_msg(EAT_ERROR);
		stop_simulation(philo);
	}
	return (EXIT_SUCCESS);
}
