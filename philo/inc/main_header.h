/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:07:56 by ufo               #+#    #+#             */
/*   Updated: 2024/12/24 16:38:20 by ufo              ###   ########.fr       */
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

enum philo_routine
{
    FORK,
    EAT,
    SLEEP,
    THINK,
    DIE
};

typedef struct s_philo {
    int             id;
    int             taken_meals_number;
    long long       last_meal_time;
    t_config        *root_config;
    pthread_t       philo_thread;
    pthread_mutex_t last_meal_time_mutex;
    pthread_mutex_t taken_meals_number_mutex;
    pthread_mutex_t *own_fork;
    pthread_mutex_t *neighbor_fork;
    t_philo         *next;
    t_philo         *prev;  
} t_philo;

typedef struct s_config {
    int philo_number;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int meals_number;
    long long       initial_time;
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
void        ft_clean_up_philo_list(t_philo **philo);
t_philo     *ft_init_philo(t_config *config, t_philo *prev_philo);
void        ft_clean_up_forks(pthread_mutex_t **mutex_arr, int created_num);
t_config    *ft_init_config(char **argv);

//Print master
void    ft_print_master(t_philo *philo, int philo_state);

//Time Master
long long   ft_get_now_stamp_mls(void);
long long   ft_get_elapsed_time(long long start_time);

//utils
int ft_find_last_philo_id(t_config **config);

//Syncher
void ft_synchronize_philosophers(t_philo *philo);

//Routine
void *ft_routine(void *arg);

//Debugger
void ft_print_after_init_enteties(t_config *config);

#endif
