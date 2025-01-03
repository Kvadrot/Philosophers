/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 16:40:21 by ufo               #+#    #+#             */
/*   Updated: 2024/12/25 15:16:09 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/main_header.h"

  
bool ft_check_exit(t_config *config)
{
    pthread_mutex_lock(&(config->must_exit_mutex));
    if (config->must_exit == true)
    {
        pthread_mutex_unlock(&(config->must_exit_mutex));
        // pthread_mutex_lock(&(config->print_mutex));
        // printf("philo %d detected termination, exiting...\n", philo->id);
        // pthread_mutex_unlock(&(cp_config->print_mutex));
        return (true);
    }
    pthread_mutex_unlock(&(config->must_exit_mutex));
    return (false);
}

// @MARK: ft_find_last_philo_id
// =================================================================================
// Descritption: 
//     Returns id of last created philo (philo_list.id.max)
// How_it_works:
//      1) starts while loop until temp_philo.id < max_id;
//      2) max.id = temp.philo.id
// Annotation:
// non
// =================================================================================
int ft_find_last_philo_id(t_config **config)
{
    int         max_id;
    t_config    *cp_config;
    t_philo    *temp_phillo;

    max_id = 0;
    cp_config = *config;
    temp_phillo = cp_config->philo_list;

    while (temp_phillo && temp_phillo->id > max_id)
    {
        max_id = temp_phillo->id;
        temp_phillo = temp_phillo->next; 
    }
    printf("LOG RPINT: max_id = %d", max_id);
    return (max_id);
}