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

/*===============================MONITORING MESSAGES==========================*/
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define EAT "is eating\n"
# define FORKED "has taken a fork\n"
# define DIE "died\n"

/*===============================STRUCTS======================================*/

typedef struct s_params
{
	int				philo_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_must_eat;
	struct timeval	start_time;
	pthread_mutex_t	print_mutex;
	bool			to_stop_simulation;
	pthread_mutex_t	stop_sim_mutex;
	pthread_t		monitoring_thread_id;
}	t_params;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread_id;
	pthread_mutex_t	fork_mutex;
	int				times_eaten;
	struct timeval	last_meal_time;
	pthread_mutex_t	last_meal_time_and_times_eaten_mutex;
	t_params		*prog_data;
}	t_philo;

/*===============================PARSING======================================*/
bool			is_valid_args(int argc, char **argv);

/*===============================INIT======================================*/
int				init_params_and_philos(t_philo **philo,
					t_params *prog_data, char **arg);

/*===============================UTILS======================================*/
long int		ft_atol(const char *nptr);
int				ft_strlen(char *str);
int				error_msg(char *msg);
void			clean_data(t_philo **philo, t_params *prog_data);
int				destroy_mutex_in_n_structure(t_philo *philo, int size);

/*===============================ROUTINE======================================*/
int				start_routine(t_philo *philo, t_params *prog_data);
int				routine_eat(t_philo *philo);

/*===============================ROUTINE_UTILS================================*/
int				update_last_meal_time_and_times_eaten(t_philo *philo);
int				segments_usleep(t_philo *philo, unsigned int time);
int				print_status(t_philo *philo, int id, char *str);
int				stop_simulation(t_philo *philo);
bool			should_stop_simulation(t_philo *philo);
int				get_time_stamps_ms(long long int *time_stamps_ms);
unsigned int	get_time_elapsed_ms(struct timeval *start, struct timeval *end);
bool			is_even(int num);

/*===============================MONITORING================================*/
int				start_global_monitoring_thread(t_philo *philo,
					t_params *prog_data);

#endif // !PHILO_H
