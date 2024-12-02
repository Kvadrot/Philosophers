/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:08:18 by ufo               #+#    #+#             */
/*   Updated: 2024/12/02 13:47:36 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

int ft_launch_simulation(t_config **config)
{
    t_philo *temp_philo;
    temp_philo = (*config)->philo_list;
    //Our philophers are cirlced so last is sitting next to the first philo
    // thats why while (n-1.id < n.id)
    while (temp_philo->prev->id < temp_philo->id)
    {
        
        // temp_philo->philo_thread = pthread_create()
        temp_philo = temp_philo->next;
    }
    printf("simulation is launched\n");
    return (200);
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
    ft_launch_simulation(&main_config);
    return (0);
}