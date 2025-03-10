/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-03 13:56:04 by selango           #+#    #+#             */
/*   Updated: 2024-10-03 13:56:04 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*check if the philo is dead*/

int	philo_dead(t_philo *philo,size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((philo->eating == 0) && ((get_current_time() - philo->last_meal_time) >= time_to_die))
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

/*checks if any of the philo is dead*/

int	checker_philo_dead(t_philo *philo)
{
	int	i;
	int	philo_count;

	i = 0;
	philo_count = philo[0].num_of_philos;
	while (i < philo_count)
	{
		if (philo_dead(&philo[i],philo[i].time_to_die))
		{
			print_state("died", &philo[i], philo[i].philo_id);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
            return(1);
		}
		i++;
	}
	return (0);
}
/*checks if all the philo ate the num of meals*/
int	checker_philo_ate(t_philo *philo)
{
	int	completed_eating;
	int	i;

	completed_eating = 0;
	i = 0;

	if (philo[0].nbr_meals_fed == -1)
		return (0);
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo->meal_lock);
		if (philo[i].meals_eaten >= philo[i].nbr_meals_fed)
			completed_eating++;
		pthread_mutex_unlock(philo->meal_lock);
		i++;
	}
	if (completed_eating == philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return(1);
	}
	return (0);
}
/* monitor thread function which checks the philo is dead or 
nbr_of_meals eaten exist and thn return pointer*/
void *monitor(void *pointer)
{
    t_philo *philo;
    philo = (t_philo *) pointer;
    while(1)
    {
        if(checker_philo_dead(philo) == 1 || checker_philo_ate(philo) == 1)
            break;
    }
    return(pointer);
}
