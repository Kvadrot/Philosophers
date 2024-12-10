/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:07:56 by ufo               #+#    #+#             */
/*   Updated: 2024/12/10 20:19:12 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HEADER_H
#   define MAIN_HEADER_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
#include <string.h>


typedef struct s_philo t_philo;
typedef struct s_config t_config;
struct timeval initial_time;


typedef struct s_philo {
    int             id;
    int             time_to_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             taken_meals_number;
    bool            is_dead;
    t_config        *root_config;
    pthread_t       philo_thread;
    pthread_mutex_t *own_fork;
    pthread_mutex_t *neighbor_fork;
    struct timeval  last_meal_time;
    t_philo         *next;
    t_philo         *prev;  
} t_philo;

typedef struct s_config {
    int philo_number;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int meals_number;
    struct timeval  initial_time;
    bool            must_exit;
    bool            is_synchronized;
    t_philo         *philo_list;
    pthread_mutex_t print_mutex;
    pthread_mutex_t must_exit_mutex;
    pthread_mutex_t simulation_syncher;
    pthread_mutex_t *forks_arr;
} t_config;

//validation helpers
bool	ft_isdigit(int someInt);
bool    ft_validate_input(char **argv);
void    ft_print_default_input_error_number(void);

//init  enteties
t_philo     *ft_init_philo(t_config *config, t_philo *prev_philo);
void        ft_clean_up_philo_list(t_philo **philo);
t_config    *ft_init_config(char **argv);

//utils
int ft_find_last_philo_id(t_config **config);

#endif
