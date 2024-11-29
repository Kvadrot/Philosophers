/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enteties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:24:12 by ufo               #+#    #+#             */
/*   Updated: 2024/11/29 13:24:43 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

void ft_clean_up_philo_list(t_philo **philo) {
    t_philo *temp;
    t_philo *next;
    
    if (!philo || !(*philo))
        return;
    temp = *philo;
    do {
        next = temp->next;
        free(temp);
        temp = next;
    } while (temp != *philo);
    *philo = NULL;
}


t_philo *ft_init_philo(t_config *config, t_philo *prev_philo) {
    t_philo *philo;

    if (!config)
        return (NULL);
    philo = malloc(sizeof(t_philo));
    if (!philo)
        return (NULL);
    if (prev_philo == NULL)
        philo->id = 0;
    else
        philo->id = prev_philo->id + 1;
    philo->time_to_eat = config->time_to_eat;
    philo->time_to_die = config->time_to_die; // Corrected typo
    philo->time_to_sleep = config->time_to_sleep;
    philo->meals_number = config->meals_number;
    philo->prev = prev_philo;
    philo->next = NULL;
    return (philo);
}


t_philo *ft_get_philo_list(t_config *config) {
    t_philo *philo_list;
    t_philo *temp_philo;
    int i;

    if (!config)
        return (NULL);
    i = 1;
    philo_list = ft_init_philo(config, NULL);
    if (!philo_list)
        return (NULL);
    temp_philo = philo_list;
    while (i < config->philo_number) {
        temp_philo->next = ft_init_philo(config, temp_philo);
        if (!temp_philo->next) {
            ft_clean_up_philo_list(&philo_list);
            return (NULL);
        }
        temp_philo = temp_philo->next;
        i++;
    }
    temp_philo->next = philo_list;
    philo_list->prev = temp_philo;
    return (philo_list);
}


t_config *ft_init_config(char **argv) {
    t_config *config;

    config = malloc(sizeof(t_config));
    if (!config)
        return (NULL);
    config->philo_number = atoi(argv[1]);
    config->time_to_eat = atoi(argv[2]);
    config->time_to_die = atoi(argv[3]);
    config->time_to_sleep = atoi(argv[4]);
    if (argv[5] != NULL)
        config->meals_number = atoi(argv[5]);
    else
        config->meals_number = 0; // Default to 0 for unlimited meals
    config->philo_list = ft_get_philo_list(config);
    if (!config->philo_list) {
        free(config);
        return (NULL);
    }
    printf("LOG PRINT: philo.id = %d philo.meals = %d\n", config->philo_list->id, config->meals_number);
    return (config);
}
