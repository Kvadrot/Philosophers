/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 14:23:04 by ufo               #+#    #+#             */
/*   Updated: 2024/12/24 14:35:43 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

void ft_print_after_init_enteties(t_config *config)
{
    int i = 0;
    t_philo *temp_philo;
    temp_philo = config->philo_list;
    while (i < config->philo_number)
    {
        printf("philo_%d ", temp_philo->id);

        ///CHECK for left fork
        printf("has left_fork: ");
        if (temp_philo->own_fork != NULL)
            printf("true");
        else
            printf("false");
        
        ///CHECK for right fork
        printf("has right_fork: ");
        if (temp_philo->neighbor_fork != NULL)
            printf("true");
        else
            printf("false");
        printf("\n");
        temp_philo = temp_philo->next;
    }
    
    
}