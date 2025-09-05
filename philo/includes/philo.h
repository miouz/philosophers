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
# define ERROR_ARGS_NO_CONFORM "Error: need 4 or 5 NUMERIC arguments: [number_of_philosophers]\
 [time_to_die] [time_to_eat] [time_to_sleep]\
 [number_of_times_each_philosopher_must_eat]\n"
# define ERROR_ARGS_NOPHILO "Error: need at least 1 philo -.-\n"
# define ERROR_ARGS_ZERO "Error: need no zero value for correct simulation\n"
# define ERROR_MALLOC "Error: Malloc failed\n"
# define ERROR_TIME "Error: Can't get time\n"
# define ERROR_THREAD "Error : Can't creat thread\n"
# define ERROR_EAT "Error : Can't begin to eat\n"
# define ERROR_MUTEX "Error : Can't init or destroy mutex\n"

/*===============================MONITORING MESSAGES==========================*/
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define EAT "is eating\n"
# define FORKED "has taken a fork\n"
# define DIE "died\n"

/*====================================VALUES==================================*/
# define TIME_DELAY_MONITORING_US 1000
# define TIME_INTERVAL_CHECK_IF_START_SIM_US 200
# define TIME_INTERVAL_CHECK_IF_STOP_SIM_US 1000
# define TIME_INTERVAL_CHECK_IF_START_MONITORING_US 800
# define TIME_INTERVAL_MONITORING_US 2000
# define PERCENTAGE_TIME_TO_THINK 1.1
# define TIME_TO_THINK 2

/*===============================STRUCTS======================================*/

typedef struct s_params
{
	int				philo_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	print_mutex;
	bool			begin_to_eat;
	pthread_mutex_t	begin_to_eat_mutex;
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
int				routine_sleep(t_philo *philo);
int				routine_think(t_philo *philo);
bool			should_begin_to_eat(t_philo *philo);

/*===============================EAT_ACTIONS================================*/
int				drop_two_forks(t_philo *philo, int id);
int				get_two_forks(t_philo *philo, int id);
void			one_philo_eat(t_philo *philo);

/*===============================TIME_UTILS================================*/
int				update_last_meal_time_and_times_eaten(t_philo *philo);
int				get_time_stamps_ms(long long int *time_stamps_ms);
unsigned int	get_time_elapsed_ms(struct timeval *start, struct timeval *end);

/*===============================ROUTINE_UTILS================================*/
int				segments_usleep(t_philo *philo, unsigned int time);
int				print_status(t_philo *philo, int id, char *str);
int				stop_simulation(t_philo *philo);
bool			should_stop_simulation(t_philo *philo);
bool			is_even(int num);

/*===============================MONITORING================================*/
int				start_global_monitoring_thread(t_philo *philo,
					t_params *prog_data);

#endif // !PHILO_H
