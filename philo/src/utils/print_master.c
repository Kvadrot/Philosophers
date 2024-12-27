/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:55:12 by ufo               #+#    #+#             */
/*   Updated: 2024/12/27 15:21:43 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/main_header.h"



void    ft_print_master(t_config *config, t_philo *philo, int philo_state)
{
    pthread_mutex_t print_mutex;
    long time_stamp;

    print_mutex = philo->root_config->print_mutex;
    time_stamp = ft_get_elapsed_time(philo->root_config->initial_time);
    pthread_mutex_lock(&print_mutex);
    if (ft_check_exit(config) == true)
    {
        pthread_mutex_unlock(&print_mutex);
        return ;
    }
    if (philo_state == FORK)
         printf("%ld %d hast taken a fork\n", time_stamp, philo->id);
    if (philo_state == EAT)
         printf("%ld %d is eating\n", time_stamp, philo->id);
    if (philo_state == SLEEP)
        printf("%ld %d is sleeping\n", time_stamp, philo->id);
    if (philo_state == THINK)
        printf("%ld %d is thinking\n", time_stamp, philo->id);

    pthread_mutex_unlock(&print_mutex);
}
