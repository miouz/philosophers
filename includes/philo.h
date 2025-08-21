/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhou <mzhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:23:01 by mzhou             #+#    #+#             */
/*   Updated: 2025/08/19 18:23:02 by mzhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdbool.h>

// ERROR MESSAGES
# define ARGS_ERROR "need 4 or 5 NUMERIC arguments: [number_of_philosophers]\
	[time_to_die] [time_to_eat] [time_to_sleep]\
	[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philo
{
	int				*status;
	int				*forks;
	pthread_mutex_t	*mutex;
	int				philo_num;
	int				times_must_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
}	t_philo;

int	ft_strlen(char *str);
int	error_quit(char *msg);
#endif // !PHILO_H
