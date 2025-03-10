/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 13:23:37 by selango           #+#    #+#             */
/*   Updated: 2024-10-02 13:23:37 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int valid_number(char *argv)
{
    int i;
    i =0;
    while(argv[i] != '\0')
    {
        if(argv[i] < '0' || argv[i] > '9')
            return(1);
        i++;
    }
    return(0);
}
int check_valid_input(char **argv)
{
    if(ft_atoi(argv[1]) <= 0 || valid_number(argv[1]) == 1)
        return(write(2,"Invalid Philosopher numbers\n",29),1);
    else if(ft_atoi(argv[2]) <= 0 || valid_number(argv[2]) == 1)
        return(write(2,"Invalid time to die\n",21),1);
    else if(ft_atoi(argv[3]) <= 0 || valid_number(argv[3]) == 1)
        return(write(2,"Invalid time to eat\n",21),1);
    else if(ft_atoi(argv[4]) <= 0 || valid_number(argv[4]) == 1)
        return(write(2,"Invalid time to sleep\n",23),1);
    else if(argv[5] && (ft_atoi(argv[5]) <= 0 || valid_number(argv[5]) == 1))
        return(write(2,"Invalid number of times each philosopher must eat\n",51),1);
    return(0);
}

void    parse_input(t_philo *philo,char **argv)
{
    philo->num_of_philos = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep =ft_atoi(argv[4]);
    if(argv[5])
        philo->nbr_meals_fed = ft_atoi(argv[5]);
    else
        philo->nbr_meals_fed = -1;
}
