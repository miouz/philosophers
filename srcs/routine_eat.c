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

// static int	pick_fork(t_philo *philo, int id_fork, int id_philo)
// {
// 	int	index_fork;
//
// 	index_fork = id_fork - 1;
// 	while (1)
// 	{
// 		if (philo->forks[index_fork] == FREE_TO_USE)
// 			break ;
// 	}
// 	pthread_mutex_lock(&philo->fork_mutex[index_fork]);
// 	philo->forks[id_fork - 1] = OCCUPIED;
// 	pthread_mutex_unlock(&philo->fork_mutex[index_fork]);
// 	pthread_mutex_lock(&philo->print_mutex);
// 	printf("philo[%d] has taken a fork[%d]\n", id_philo, id_fork);
// 	pthread_mutex_unlock(&philo->print_mutex);
// 	return (EXIT_SUCCESS);
// }

int	routine_eat(t_philo *philo, int id)
{
	(void)id;
	usleep(philo->time_to_eat);
	// if (id == philo->philo_num - 1)
	// {
	// 	pick_fork(philo, id - 1, id);
	// 	pick_fork(philo, id, id);
	// }
	// else
	// {
	// 	pick_fork(philo, id, id);
	// 	pick_fork(philo, id - 1, id);
	// }
	return (EXIT_SUCCESS);
}
