/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:51:59 by ufo               #+#    #+#             */
/*   Updated: 2024/12/27 19:04:09 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/main_header.h"

// @MARK: ft_eat_routine
// ================================================================================
//  Description: Handles the eating routine for a philosopher, where they take
//               two forks, eat, and then release the forks.
//  How_it_works:
//  1) If the philosopher's id is even, they pick up their own fork first, then the neighbor's fork.
//     If the philosopher's id is odd, they pick up the neighbor's fork first, then their own fork.
//  2) The philosopher locks their first fork (either own or neighbor's).
//  3) The philosopher locks their second fork (the other one).
//  4) The philosopher simulates eating by sleeping for the specified time.
//  5) The philosopher unlocks their second fork.
//  6) The philosopher unlocks their first fork.
// =================================================================================

void ft_eat_routine(t_config *config ,t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    // Always lock the fork with the smaller address first
    if (philo->id % 2 == 0)
    {
        first_fork = philo->own_fork;
        second_fork = philo->neighbor_fork;
    }
    else
    {
        first_fork = philo->neighbor_fork;
        second_fork = philo->own_fork;
    }

    pthread_mutex_lock(first_fork);
    if (ft_check_exit(philo->root_config))
    {
        pthread_mutex_unlock(first_fork);
        return;
    }
    ft_print_master(config, philo, FORK);

    pthread_mutex_lock(second_fork);
    if (ft_check_exit(philo->root_config))
    {
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        return;
    }
    ft_print_master(config, philo, FORK);

    // Eating phase
    pthread_mutex_lock(&philo->last_meal_time_mutex);
    ft_print_master(config, philo, EAT);
    philo->last_meal_time = ft_get_now_stamp_mls();
    pthread_mutex_unlock(&philo->last_meal_time_mutex);
    
    pthread_mutex_lock(&philo->taken_meals_number_mutex);
        philo->taken_meals_number += 1;
    pthread_mutex_unlock(&philo->taken_meals_number_mutex);
    usleep(ft_convert_mls_into_mcrs(philo->root_config->time_to_eat));

    // Unlock forks in reverse order
    pthread_mutex_unlock(first_fork);
    pthread_mutex_unlock(second_fork);
}

void ft_think_routine(t_config *config, t_philo *philo)
{
    long long time_to_think;
    long long multiplyer;
    
    if (ft_check_exit(philo->root_config))
        return;
    multiplyer = 1 + (config->philo_number % 2);
    ft_print_master(config, philo, THINK);
    time_to_think = (philo->root_config->time_to_eat * multiplyer) - config->time_to_sleep;
    usleep(ft_convert_mls_into_mcrs(time_to_think));
}

void ft_sleep_routine(t_config *config, t_philo *philo)
{
    if (ft_check_exit(philo->root_config))
        return;
    ft_print_master(config, philo, SLEEP);
    usleep(ft_convert_mls_into_mcrs(philo->root_config->time_to_sleep));
}

 void *ft_routine(void *arg)
 {
    t_philo *philo;
    t_config *cp_config;
    
    philo = (t_philo *)arg;
    cp_config = philo->root_config;
    // ft_synchronize_philosophers(philo);

    pthread_mutex_lock(&philo->last_meal_time_mutex);
    philo->last_meal_time = ft_get_now_stamp_mls();
    pthread_mutex_unlock(&philo->last_meal_time_mutex);
    
    while ((ft_check_exit(cp_config) == false))
    {
        ft_eat_routine(cp_config, philo);
        ft_sleep_routine(cp_config, philo);
        ft_think_routine(cp_config, philo);
    }
    return (0);
 }