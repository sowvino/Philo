/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 12:07:38 by selango           #+#    #+#             */
/*   Updated: 2024-10-02 12:07:38 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

#define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				num_of_philos;
	int				philo_id;
	int				eating;
	int				meals_eaten;
	int				nbr_meals_fed;
	int				*dead;
	size_t			last_meal_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
}					t_philo;

typedef struct s_lock
{
	int				dead_flag;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philo;
}					t_lock;
/*main functions*/
int valid_number(char *argv);
int check_valid_input(char **argv);
void    parse_input(t_philo *philo,char **argv);

/*Data init functions*/
void init_lock(t_lock *lock, t_philo *philo);
void init_forks(pthread_mutex_t *forks, int philo_nbr);
void init_philos(t_philo *philo, t_lock *lock, pthread_mutex_t *forks, char **argv);

/*routines*/
void print_state(char *str,t_philo *philo,int id);
void think(t_philo *philo);
void ft_sleep(t_philo *philo);
void eat(t_philo *philo);

/*monitor*/
int	philo_dead(t_philo *philo,size_t time_to_die);
int	checker_philo_dead(t_philo *philo);
int	checker_philo_ate(t_philo *philo);
void *monitor(void *pointer);

/*create thread*/
int     dead_loop(t_philo *philo);
void *philo_state(void *pointer);
int start_dinner(t_lock *lock, pthread_mutex_t *forks);

/*destroy threads*/
void	destroy_all(char *str, t_lock *lock,pthread_mutex_t *forks);

/*utilis*/
int ft_atoi(char *str);
void error_msg(char *error);
size_t get_current_time();
int ft_usleep(size_t millisecond);

#endif
