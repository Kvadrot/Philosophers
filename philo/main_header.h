/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:07:56 by ufo               #+#    #+#             */
/*   Updated: 2024/11/28 20:48:03 by ufo              ###   ########.fr       */
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

typedef struct s_philo t_philo;

typedef struct s_philo {
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int meals_number;
    t_philo *next;
    t_philo *prev;
} t_philo;

typedef struct s_config {
    int philo_number;
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int meals_number;
    t_philo *philo_list;
} t_config;

//validation helpers
bool	ft_isdigit(int someInt);
bool    ft_validate_input(char **argv);
void    ft_print_default_input_error_number(void);

#endif
