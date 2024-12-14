/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:08:18 by ufo               #+#    #+#             */
/*   Updated: 2024/12/14 12:48:13 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 # include "../main_header.h"

void ft_synchronize_philosophers(t_philo *philo)
{
    t_config *cp_config;
    cp_config = philo->root_config;

    while (1)
    {
        pthread_mutex_lock(&(cp_config->must_exit_mutex));
        if (cp_config->must_exit == true)
        {
            pthread_mutex_unlock(&(cp_config->must_exit_mutex));
            pthread_mutex_lock(&(cp_config->print_mutex));
            printf("philo %d detected termination, exiting...\n", philo->id);
            pthread_mutex_unlock(&(cp_config->print_mutex));
            pthread_mutex_unlock(&(cp_config->must_exit_mutex));
            exit(3);
        }
        pthread_mutex_unlock(&(cp_config->must_exit_mutex));
        
        pthread_mutex_lock(&(cp_config->simulation_syncher));
        if (cp_config->is_synchronized == true)
        {
            pthread_mutex_unlock(&(cp_config->simulation_syncher));

            pthread_mutex_lock(&(cp_config->print_mutex));
            printf("philo %d has started\n", philo->id);
            pthread_mutex_unlock(&(cp_config->print_mutex));
            pthread_mutex_unlock(&(cp_config->simulation_syncher));
            break;
        }
        pthread_mutex_unlock(&(cp_config->simulation_syncher));

        usleep(1); // Prevent busy-waiting
    }
}


void    ft_print_master(t_philo *philo, int philo_state)
{
    pthread_mutex_t print_mutex;
    long time_stamp;

    print_mutex = philo->root_config->print_mutex;
    time_stamp = ft_get_elapsed_time(philo->root_config->initial_time);
    pthread_mutex_lock(&print_mutex);
    if (philo_state == FORK)
         printf("%ld %d hast taken a fork\n", time_stamp, philo->id);
    if (philo_state == EAT)
         printf("%ld %d is eating\n", time_stamp, philo->id);
    if (philo_state == SLEEP)
        printf("%ld %d is sleeping\n", time_stamp, philo->id);
    if (philo_state == THINK)
        printf("%ld %d is thinking\n", time_stamp, philo->id);

    pthread_mutex_unlock(&print_mutex);
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
    int i;
    i = 0;
    t_philo *philo;
    philo = (t_philo *)arg;
    ft_synchronize_philosophers(philo);
    if (philo->id % 2 != 0)
    {
        pthread_mutex_lock((philo->own_fork));
        ft_print_master(philo, FORK);
        pthread_mutex_lock((philo->neighbor_fork));
        ft_print_master(philo, FORK);
        
        ft_print_master(philo, EAT);
        usleep(philo->time_to_eat);
        pthread_mutex_unlock((philo->neighbor_fork)); 
        pthread_mutex_unlock((philo->own_fork));        
    }
    // while (i)
    // {
    //     ft_print_master(philo, FORK);
    //     printf("philo %d is thinking \n", philo->id);
    //     usleep(10000);
    //     printf("philo %d has taken forks\n", philo->id);
    //     usleep(10000);
    //     printf("philo %d philo is eatting\n",  philo->id);
    //     usleep(10000);
    //     printf("philo %d has finished meal %d\n", philo->id, philo->taken_meals_number);
    //     usleep(10000);
    //     printf("philo %d, is sleeping\n", philo->id);
    //     usleep(10000);
    //     i++;
    // }
    return (0);
 }

// @MARK: ft_cleanup_threads
// ================================================================================
//  Descritption: make main-thread to wait for created threads to finish execution
//  How_it_works:
// 1) iterates through each created thread before current philo
// =================================================================================
//
void ft_cleanup_threads(t_philo *start_philo, t_philo *current_philo, t_config **config)
{
    t_philo *temp_philo;
    t_config *cp_config;
    cp_config = *config;
    temp_philo = start_philo;

    // Iterate through all philosophers up to the current one
    pthread_mutex_lock(&(cp_config->must_exit_mutex));
    cp_config->must_exit = true;
    printf("LOG: ft_cleanup_threads was triggered, must_eixt is true");
    pthread_mutex_unlock(&(cp_config->must_exit_mutex));

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
    while (temp_philo->next->id != 0)
    {
        pthread_join(temp_philo->philo_thread, NULL);
        temp_philo = temp_philo->next;
    }
    pthread_join(temp_philo->philo_thread, NULL);
 }

// @MARK: ft_launch_simulation
// =================================================================================
// Descritption:
//      launches entire simulation
// How_it_works:
//      1) Creates threads(philosophers)
//      2) Check philo num if there is only one philo starts special case 
//      3) Creates threads one by one;
//      4) We have to launch one thread separatly to allow last thread to be started
//      due to our while statement
//      5) Swithes is_synchrozed to true as all threads are created.
//      6) Init simulation launching time
// =================================================================================
//
int ft_launch_simulation(t_config **config)
{
    t_philo *temp_philo;
    temp_philo = (*config)->philo_list;
    //Our philophers are cirlced so last is sitting next to the first philo
    // thats why while (n-1.id < n.id)
    while (temp_philo->next->id != 0)
    {
        printf("DEBUG: temp_phiilo_id = %d, has been created\n", temp_philo->id);
       if (pthread_create(&(temp_philo->philo_thread), NULL, &(ft_routine), temp_philo) != 0)
       {
            //TODO: terminate created threads
            ft_cleanup_threads((*config)->philo_list, temp_philo, config);
            return (2);
       }
        temp_philo = temp_philo->next;
    }
    if (pthread_create(&(temp_philo->philo_thread), NULL, &(ft_routine), temp_philo) != 0)
    {
        ft_cleanup_threads((*config)->philo_list, temp_philo, config);
        return (2);
    }
    pthread_mutex_lock(&(*config)->simulation_syncher);
    (*config)->is_synchronized = true;
    //svae launch time
    printf("LOG PRINT: simulation is successully launched \n");
    pthread_mutex_unlock(&(*config)->simulation_syncher);
    gettimeofday(&((*config)->initial_time), NULL);
    ft_stop_simulation(config);
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