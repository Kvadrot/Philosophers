/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:08:18 by ufo               #+#    #+#             */
/*   Updated: 2024/12/06 18:25:32 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "../main_header.h"

long get_elapsed_time(struct timeval start) {
    struct timeval now;
    gettimeofday(&now, NULL);

    return ((now.tv_sec - start.tv_sec) * 1000) + 
           ((now.tv_usec - start.tv_usec) / 1000);
}


// @MARK: ft_launch_simulation
// =================================================================================
// Descritption: 
//      Makes created threads to wait for creating others, to ensure in simultaneously
//      launch of simulation;    
// How_it_works:
//      1) launch infinity loop with few if statements
//      2) check for exit flag: config->must_exit
//      3) check for synchronized flag: config->is_synchronized
// Annotation
//      We need this func until main thread ft_launch_simulation will create all threads
// =================================================================================
void    ft_synchronize_philosophers(t_config **config)
{
    
}

// @MARK: ft_launch_simulation
// =================================================================================
// Descritption: 
//      Simulates philo routine: eat -> think -> sleep
// How_it_works:
//      1) 
//      2) 
//      3) 
// =================================================================================

 void *ft_routine(void *arg)
 {
    t_philo *philo;
    philo = (t_philo *)arg;
    while (1)
    {
        printf("philo %d is thinking \n", philo->id);
        usleep(10000);
        printf("philo %d has taken forks\n", philo->id);
        usleep(10000);
        printf("philo %d philo is eatting\n",  philo->id);
        usleep(10000);
        printf("philo %d has finished meal %d", philo->id, philo->taken_meals_number);
        usleep(10000);
        printf("philo %d, is sleeping", philo->id);
        usleep(10000);
    }
 }

// @MARK: ft_cleanup_threads
// =================================================================================
//  Descritption: make main-thread to wait for created threads to finish execution
//  How_it_works:
// 1) iterates through each created thread before current philo
// =================================================================================
//
void ft_cleanup_threads(t_philo *start_philo, t_philo *current_philo)
{
    t_philo *temp_philo;

    temp_philo = start_philo;

    // Iterate through all philosophers up to the current one
    while (temp_philo != current_philo)
    {
        if (temp_philo->philo_thread)
        {
            pthread_join(temp_philo->philo_thread, NULL); // Wait for the thread to finish
        }
        temp_philo = temp_philo->next;
    }
}


 void ft_stop_simulation(t_config **config)
 {
    t_philo *temp_philo;
    
    temp_philo = (*config)->philo_list;
    while (temp_philo->prev->id < temp_philo->id)
    {
        
        pthread_join(temp_philo->philo_thread, NULL);
        temp_philo = temp_philo->next;
    }
 }

// @MARK: ft_launch_simulation
// =================================================================================
// Descritption:
//      launches entire simulation
// How_it_works:
//      1) Creates threads(philosophers)
//      2) Check philo num if there is only one philo starts special case 
//      3) Synchronize philosophers to start executing at the same time
// =================================================================================
//
int ft_launch_simulation(t_config **config)
{
    t_philo *temp_philo;
    
    temp_philo = (*config)->philo_list;
    //Our philophers are cirlced so last is sitting next to the first philo
    // thats why while (n-1.id < n.id)
    while (temp_philo->prev->id < temp_philo->id)
    {
       if (pthread_create(&(temp_philo->philo_thread), NULL, &(ft_routine), temp_philo) != 0)
       {
            return (2);
       }
        temp_philo = temp_philo->next;
    }
    printf("simulation is launched\n");

    ft_stop_simulation(config);
    printf("simulation is stopped\n");
    return (0);
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
    {
        printf("failed to laucnh simulation config doesnt exist \n");
        return(1);
    }

    ft_launch_simulation(&main_config);
    return (0);
}