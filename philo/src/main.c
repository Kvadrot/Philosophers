/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:08:18 by ufo               #+#    #+#             */
/*   Updated: 2024/11/28 21:15:33 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

t_config *ft_init_config(char **argv)
{
    t_config   *config;

    config = malloc(sizeof(t_config) * 1);
    if (!config)
        return (NULL);
    config->philo_number = atoi(argv[1]);
    config->time_to_eat = atoi(argv[2]);
    config->time_to_die = atoi(argv[3]);
    config->time_to_sleep = atoi(argv[4]);
    if (argv[5])
        config->meals_number = atoi(argv[5]);
    else
        config->meals_number = 1;
    config->philo_list = NULL;
    printf("LOG PRINT: philo_number = %d \n", config->philo_number);
    return(config);
}

t_philo *ft_init_philo(t_config *config, t_philo *prev_philo)
{
    t_philo *philo;
    if (!config)
        return (NULL);
    philo = malloc(sizeof(t_philo) * 1);
    if (!philo)
        return (NULL);
    philo->time_to_eat = config->time_to_eat;
    philo->time_to_die = config->time_to_eat;
    philo->time_to_sleep = config->time_to_sleep;
    philo->meals_number = config->meals_number;
    if (prev_philo == NULL)
        philo->prev = NULL;
    else
        philo->prev = NULL;
    philo->next = NULL;
    return (philo);
}

void    ft_clean_up_philo_list(t_philo **philo)
{
    t_philo *next_philo;
    t_philo *temp_philo;

    temp_philo = *philo;
    while (temp_philo->prev != NULL)
        temp_philo = temp_philo->next;
    temp_philo = *philo;
    while (temp_philo)
    {
        next_philo = temp_philo->next;
        free(temp_philo);
        temp_philo = next_philo;
    }
}

t_philo *ft_get_philo_list(t_config *config)
{
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
    while (i < config->meals_number)
    {
        temp_philo->next = ft_init_philo(config, temp_philo);
        if (!temp_philo)
        {
            ft_clean_up_philo_list(&temp_philo);
            return (NULL);
        }
        temp_philo = temp_philo->next;
        i++;
    }
    
}

int main(int argc, char **argv)
{
    t_config *main_config;

    if (5 > argc || argc > 6)
    {    
        ft_print_default_input_error_number();
        return (0);
    }
    if (ft_validate_input(argv) == false)
    {
        printf("wrong param, pls provide digits only\n");
        return (1);
    }
    main_config = ft_init_config(argv);
    if (!main_config)
        return(1);
    // ft_launch_simulation();
    return (0);
}