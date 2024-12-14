/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:36:10 by ufo               #+#    #+#             */
/*   Updated: 2024/12/14 11:43:53 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

// @MARK: get_elapsed_time
// =================================================================================
// Descritption: 
//      Calculates elapsed time from given time
// How_it_works:
// =================================================================================
//
long ft_get_elapsed_time(struct timeval start)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    return ((now.tv_sec - start.tv_sec) * 1000) + 
           ((now.tv_usec - start.tv_usec) / 1000);
}

static void print_time(struct timeval *tv) {
    printf("Time: %ld seconds, %d microseconds\n", tv->tv_sec, tv->tv_usec);
}

void    ft_print_timestamp(t_philo *philo)
{
    pthread_mutex_lock(&philo->root_config->print_mutex);
    
    pthread_mutex_unlock(&philo->root_config->print_mutex);
}
