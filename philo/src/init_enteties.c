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

void ft_clean_up_forks(pthread_mutex_t **mutex_arr, int created_num)
{
    int counter;
    pthread_mutex_t temp_fork;

    counter = 0;
    temp_fork = (*mutex_arr)[0];
    if (created_num == 1)
    {
        free(*mutex_arr);
        free(mutex_arr);
        return ;
    }
    while (created_num > counter)
    {
        pthread_mutex_destroy(&temp_fork);
        temp_fork = (*mutex_arr)[counter];
        counter++;
    }
    free(mutex_arr);
}

pthread_mutex_t *ft_init_forks(t_config **config)
{
    int counter;
    pthread_mutex_t *mutex_arr;

    counter = 0;
    // Allocate memory for the mutex array
    mutex_arr = malloc(sizeof(pthread_mutex_t) * (*config)->philo_number);
    if (mutex_arr == NULL) // Correct pointer check
        return (NULL);

    // Initialize each mutex in the array
    while (counter < (*config)->philo_number)
    {
        if (pthread_mutex_init(&mutex_arr[counter], NULL) != 0)
        {
            ft_clean_up_forks(&mutex_arr, counter); // Pass 'counter' as range
            return (NULL);
        }
        counter++;
    }
    return (mutex_arr);
}

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
    memset(philo, 0, sizeof(t_philo));
    if (prev_philo == NULL)
        philo->id = 0;
    else
        philo->id = prev_philo->id + 1;
    philo->root_config = config;
    // philo->taken_meals_number = 0;
    // philo->is_dead = false;
    // philo->philo_thread = false;
    // philo->own_fork = NULL;
    // philo->neighbor_fork = NULL; 
    // philo->prev = prev_philo;
    // philo->next = NULL;
    return (philo);
}


t_philo *ft_init_philo_list(t_config *config)
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

void ft_set_forks_for_philo(t_config **config)
{
    int i;
    t_philo *temp_philo;
    temp_philo = (*config)->philo_list;
    i = 0;
    while ((*config)->philo_number > i)
    {
        temp_philo->own_fork = &(*config)->forks_arr[i];
        if (i == 0)
            temp_philo->neighbor_fork = &(*config)->forks_arr[(*config)->philo_number - 1];
        else 
            temp_philo->neighbor_fork = &(*config)->forks_arr[i - 1];
        temp_philo = temp_philo->next;
        i++;
    }

}

t_config *ft_init_config(char **argv) {
    t_config *config;

    config = malloc(sizeof(t_config));
    if (!config)
        return (NULL);
    memset(config, 0, sizeof(t_config));
    config->must_exit = false;
    config->is_synchronized = false;
    config->philo_number = atoi(argv[1]);
    config->time_to_eat = atoi(argv[2]);
    config->time_to_die = atoi(argv[3]);
    config->time_to_sleep = atoi(argv[4]);
    // memset(config->initial_time, 0 ,sizeof(config->initial_time));
    if (argv[5] != NULL)
        config->meals_number = atoi(argv[5]);
    else
        config->meals_number = 1;
    
    if (pthread_mutex_init(&(config->print_mutex), NULL) != 0)
    {
        free(config);
        return (NULL);
    }
    if (pthread_mutex_init(&(config->simulation_syncher), NULL) != 0)
    {
        pthread_mutex_destroy(&(config->print_mutex));
        free(config);
        return (NULL);
    }
    if (pthread_mutex_init(&(config->must_exit_mutex), NULL) != 0)
    {
        pthread_mutex_destroy(&(config->print_mutex));
        pthread_mutex_destroy(&(config->simulation_syncher));
        free(config);
        return (NULL);
    }
    config->forks_arr = ft_init_forks(&config);
    if (config->forks_arr == NULL)
    {
        pthread_mutex_destroy(&(config->print_mutex));
        pthread_mutex_destroy(&(config->simulation_syncher));
        pthread_mutex_destroy(&(config->must_exit_mutex));

        free(config);
        return (NULL);
    }
    config->philo_list = ft_init_philo_list(config);
    if (!config->philo_list) {
        ft_clean_up_forks(&(config->forks_arr), config->philo_number);
        pthread_mutex_destroy(&(config->print_mutex));
        pthread_mutex_destroy(&(config->simulation_syncher));
        pthread_mutex_destroy(&(config->must_exit_mutex));
        free(config);
        return (NULL);
    }
    ft_set_forks_for_philo(&config);
    printf("LOG PRINT: config.philo_num = %d philo.meals = %d\n", config->philo_number, config->meals_number);
    return (config);
}
