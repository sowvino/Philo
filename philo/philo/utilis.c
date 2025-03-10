/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 13:07:22 by selango           #+#    #+#             */
/*   Updated: 2024-10-02 13:07:22 by selango          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(char *str)
{
    unsigned long long nbr;
    int  i;
    int sign ;

    i =0;
    sign = 1;
    nbr = 0;
    while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
    {
        i++;
    }
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            sign = -1;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9')
    {
        nbr = (str[i] - '0') + (nbr * 10);
        i++;
    }
    return(nbr * sign);
}
void error_msg(char *error)
{
    printf("%s\n",error);
    return;
}

size_t get_current_time()
{
    struct timeval time;
    if(gettimeofday(&time,NULL) == -1)  
    {
        error_msg("time_stamp error");
    }
    return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_usleep(size_t millisecond)
{
    size_t start;
    start = get_current_time();
    while((get_current_time() - start ) < millisecond)
        usleep(100);
    return(0);
}
