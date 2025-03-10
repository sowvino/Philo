/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-05 13:56:08 by selango           #+#    #+#             */
/*   Updated: 2024-11-05 13:56:08 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*destroy all the thread*/
void	destroy_all(char *str, t_lock *lock,pthread_mutex_t *forks)
{
	int i ;

  i =0;
  if (str)
		printf("%s", str);
  pthread_mutex_destroy(&lock->write_lock);
  pthread_mutex_destroy(&lock->meal_lock);
  pthread_mutex_destroy(&lock->dead_lock);
  while(i < lock->philo[0].num_of_philos)
  {
    pthread_mutex_destroy(&forks[i]);
    i++;
  }
}
