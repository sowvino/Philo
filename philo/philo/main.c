/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 12:52:29 by selango           #+#    #+#             */
/*   Updated: 2024-10-02 12:52:29 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


/*
input [nbr of philo,time_to_die,time_to_eat,time_to_sleep]
./philo [5,800,200,200,optional(number of )]
*/

int main(int argc,char **argv)
{
    t_philo philo[PHILO_MAX];
    t_lock lock;
    pthread_mutex_t forks[PHILO_MAX];
    if(check_valid_input(argv) == 1)
        return(1);
    if(argc == 5 || argc == 6)
    {
        init_lock(&lock, philo);
        init_forks(forks,ft_atoi(argv[1]));
        init_philos(philo,&lock, forks, argv);
        start_dinner(&lock,forks);
        destroy_all(NULL, &lock, forks);
        return(0);
    }
    else
    {
        error_msg("Enter correct number of arguments");
        return(1);
    }
}