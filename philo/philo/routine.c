/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 13:51:39 by selango           #+#    #+#             */
/*   Updated: 2024-10-03 13:51:39 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*print_state*/
void print_state(char *str,t_philo *philo,int id)
{
    size_t time;
    pthread_mutex_lock(philo->write_lock);
    time = get_current_time() - philo->start_time;
    if(dead_loop(philo))
    {
      pthread_mutex_unlock(philo->write_lock);
      return;
    } 
    printf("%zu   %d  %s\n", time, id, str);
    pthread_mutex_unlock(philo->write_lock);
}
/*print think status of philos*/
void think(t_philo *philo)
{
    print_state("is Thinking",philo,philo->philo_id);
}
/*prints sleep status of philos*/
void ft_sleep(t_philo *philo)
{
    print_state("is Sleeping", philo, philo->philo_id);
    ft_usleep(philo->time_to_sleep);
}
/*prints eating status of philos*/
void eat(t_philo *philo)
{
  pthread_mutex_lock(philo->l_fork);
  print_state("has taken a left fork",philo, philo->philo_id);
  if(philo->num_of_philos == 1)
  {
    ft_usleep(philo->time_to_die);
    pthread_mutex_unlock(philo->l_fork);
    return;
  }
  pthread_mutex_lock(philo->r_fork);
  print_state("has taken a right fork",philo, philo->philo_id);
  pthread_mutex_lock(philo->meal_lock);
  philo->eating = 1;
  philo->last_meal_time = get_current_time();
  philo->meals_eaten++;
  pthread_mutex_unlock(philo->meal_lock);
  print_state("is eating ", philo, philo->philo_id);
  ft_usleep(philo->time_to_eat);
  pthread_mutex_lock(philo->meal_lock);
  philo->eating = 0;
  pthread_mutex_unlock(philo->meal_lock);
  pthread_mutex_unlock(philo->l_fork);
  pthread_mutex_unlock(philo->r_fork);
}

