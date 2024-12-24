/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:51:59 by ufo               #+#    #+#             */
/*   Updated: 2024/12/24 14:54:18 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "../main_header.h"

void ft_eat_routine(t_philo *philo)
{
    pthread_mutex_lock((philo->own_fork));
    ft_print_master(philo, FORK);
    pthread_mutex_lock((philo->neighbor_fork));
    ft_print_master(philo, FORK);
    
    ft_print_master(philo, EAT);
    usleep(philo->root_config->time_to_eat);
    pthread_mutex_unlock((philo->neighbor_fork)); 
    pthread_mutex_unlock((philo->own_fork));
}

void ft_think_routine(t_philo *philo)
{
    ft_print_master(philo, THINK);
}

void ft_sleep_routine(t_philo *philo)
{
    ft_print_master(philo, SLEEP);
    usleep(philo->root_config->time_to_sleep);
}

// @MARK: ft_launch_simulation
// =================================================================================
// Descritption: 
//      Simulates philo routine: eat -> think -> sleep
// How_it_works:
//      1) 
//      2) 
//      3) 
// =================================================================================

 void *ft_routine(void *arg)
 {
    int i;
    i = 0;
    t_philo *philo;
    philo = (t_philo *)arg;
    ft_synchronize_philosophers(philo);
    if (philo->id % 2 != 0)
    {
        ft_eat_routine(philo);
    } else {
        ft_think_routine(philo);
    }
    
    while (i)
    {
        ft_sleep_routine(philo);
        ft_eat_routine(philo);
        ft_think_routine(philo);
        i++;
    }
    return (0);
 }