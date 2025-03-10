/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 11:51:52 by selango           #+#    #+#             */
/*   Updated: 2024-10-03 11:51:52 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*initial value of philosophers--> philo id, eating,meals_eaten,
last_meal,write_lock,
*/
void init_philos(t_philo *philo,t_lock *lock,pthread_mutex_t *forks,
                char **argv)
{
    int i ;

    i =0;
    while (i < ft_atoi(argv[1]))
    {
        philo[i].philo_id = i + 1;
        philo[i].eating = 0;
        philo[i].meals_eaten  = 0;
        parse_input(&philo[i],argv);
        philo[i].start_time = get_current_time();
        philo[i].last_meal_time = get_current_time();
        philo[i].write_lock = &lock->write_lock;
        philo[i].meal_lock = &lock->meal_lock;
        philo[i].dead_lock = &lock->dead_lock;
        philo[i].dead = &lock->dead_flag;
        philo[i].l_fork = &forks[i];
        if(i == 0)
            philo[i].r_fork = &forks[philo[i].num_of_philos - 1];
        else
            philo[i].r_fork = &forks[i -1];
        i++;
    }
}

//init forks  
void init_forks(pthread_mutex_t *forks, int philo_nbr)
{
    int i;
    i =0;
    while(i < philo_nbr)
    {
        pthread_mutex_init(&forks[i],NULL);
        i++;
    }
}
void init_lock(t_lock *lock,t_philo *philo)
{
    lock->philo = philo;
    lock->dead_flag = 0;
    pthread_mutex_init(&lock->write_lock,NULL);
    pthread_mutex_init(&lock->dead_lock,NULL);
    pthread_mutex_init(&lock->meal_lock,NULL);  
}
