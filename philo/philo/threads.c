/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 13:33:16 by selango           #+#    #+#             */
/*   Updated: 2024-10-03 13:33:16 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// dead_loop initialising
int     dead_loop(t_philo *philo)
{
    pthread_mutex_lock(philo->dead_lock);
    if(*philo->dead == 1)
    {
        pthread_mutex_unlock(philo->dead_lock);
        return(1);
    }
    pthread_mutex_unlock(philo->dead_lock);
    return(0);
}

// philo_routine actions
void *philo_state(void *pointer)
{
    t_philo *philo;
    philo = (t_philo *)pointer;
    if(philo->philo_id % 2 == 0)
        ft_usleep(1);
    while(!dead_loop(philo))
    {
        eat(philo);
        ft_sleep(philo);
        think(philo);
    }
    return(pointer);
}

int start_dinner(t_lock *lock, pthread_mutex_t *forks)
{
    pthread_t observer;
    int i;

    i = 0;
    if(pthread_create(&observer, NULL, &monitor, lock->philo) != 0)
        destroy_all("Error in creating thread",lock, forks);
    while(i < lock->philo[0].num_of_philos)
    {
        if( pthread_create (&lock->philo[i].thread, NULL, &philo_state,
                            &lock->philo[i]) != 0)
            destroy_all("Error in creating thread", lock, forks); 
        i++;
    }
    i = 0;
    if (pthread_join(observer, NULL) != 0)
        destroy_all("Error in Thread join", lock, forks);
    while(i < lock->philo[0].num_of_philos)
    {
        if(pthread_join(lock->philo[i].thread, NULL) != 0)
            destroy_all("Error in Thread Join", lock , forks);
        i++;
    }
    return(0);
}