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
# include <string.h>
# include <sys/time.h>
# include <stdio.h>

/*===============================ERROR MESSAGES===============================*/
# define ARGS_ERROR "Error: need 4 or 5 NUMERIC arguments: [number_of_philosophers]\
 [time_to_die] [time_to_eat] [time_to_sleep]\
 [number_of_times_each_philosopher_must_eat]\n"
# define ARGS_ERROR_NOPHILO "Error: need at least 1 philo -.-\n"
# define MALLOC_ERROR "Error: Malloc failed\n"
# define TIME_ERROR "Error: Can't get time\n"
# define THREAD_ERROR_CREAT "Error : Can't creat thread\n"

/*===============================STRUCTS======================================*/
typedef struct s_philo
{
	int				philo_id;
	int				status;
	unsigned char	forks;
	pthread_mutex_t	mutex;
	pthread_t		thread_ids;
}	t_philo;

typedef struct s_phi_data
{
	bool			to_stop_simulation;
	struct timeval	time;
	int				philo_num;
	int				times_must_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	t_philo			*philo;

}	t_phi_data;

enum e_philo_status
{
	ONE_FORKED,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

/*===============================PARSING======================================*/
bool		is_valid_args(int argc, char **argv);

/*===============================INIT======================================*/
int			init_philos(t_philo *philo, char **argv);

/*===============================UTILS======================================*/
long int	ft_atol(const char *nptr);
int			ft_strlen(char *str);
void		free_philos(t_philo *philos);
int			error_msg(char *msg);

/*===============================THREAD======================================*/
int			start_routine(t_philo *philos);

#endif // !PHILO_H
