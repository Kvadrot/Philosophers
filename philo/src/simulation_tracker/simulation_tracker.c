/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_tracker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:10:09 by ufo               #+#    #+#             */
/*   Updated: 2024/12/25 16:03:34 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/main_header.h"

void    ft_activate_termination_simulation(t_config * config, t_philo *dead_philo)
{
    long long   now_time_stamp;
    long long   death_time;

    now_time_stamp = ft_get_now_stamp_mls();
    death_time = ft_get_elapsed_time(config->initial_time);

    pthread_mutex_lock(&config->must_exit_mutex);
    config->must_exit = true;
    pthread_mutex_unlock(&config->must_exit_mutex);
    pthread_mutex_lock(&config->print_mutex);
    printf("%lld %d is dead\n",death_time, dead_philo->id);
    pthread_mutex_unlock(&config->print_mutex);
    return ;
}

bool ft_check_is_starving(t_config *config, t_philo* temp_philo)
{
    pthread_mutex_lock(&temp_philo->last_meal_time_mutex);
    if (config->time_to_die < ft_get_elapsed_time(temp_philo->last_meal_time))
    {
        pthread_mutex_unlock(&temp_philo->last_meal_time_mutex);
        return (true);
    }
    pthread_mutex_unlock(&temp_philo->last_meal_time_mutex);
    return (false);
}

bool ft_check_everyone_is_full(t_config *config)
{
    
    return (false);
}

void *ft_track_simualtion(void *arg)
{
    t_philo *temp_philo;
    t_config *config;
    config = (t_config *)arg;
    temp_philo = config->philo_list;
    
    while (1)
    {
        if (ft_check_exit(config) == true)
            return(NULL);
        if (ft_check_is_starving(config ,temp_philo) == true)
        {
            ft_activate_termination_simulation(config, temp_philo);
            return (NULL);
        }
        temp_philo = temp_philo->next;
    }
    return (NULL);   
}