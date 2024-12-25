/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:08:18 by ufo               #+#    #+#             */
/*   Updated: 2024/12/25 15:01:14 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/main_header.h"


static bool    ft_check_are_synchronized(t_config *config)
{
    pthread_mutex_lock(&(config->simulation_syncher));
    if (config->is_synchronized == true)
    {
        pthread_mutex_unlock(&(config->simulation_syncher));
        // pthread_mutex_lock(&(config->print_mutex));
        // printf("philo %d has started\n", philo->id);
        // pthread_mutex_unlock(&(config->print_mutex));
        return (true);
    }
    pthread_mutex_unlock(&(config->simulation_syncher));
    return (false);
}

void ft_synchronize_philosophers(t_philo *philo)
{
    t_config *cp_config;
    cp_config = philo->root_config;

    while (1)
    {
        if (ft_check_exit(cp_config) == true)
            return ;
        if (ft_check_are_synchronized(cp_config) == true)
            break;
        usleep(1); // Prevent busy-waiting
    }
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

void    ft_destroy_simultion(t_config **config)
{
    ft_clean_up_philo_list(&(*config)->philo_list);
    ft_clean_up_forks(&(*config)->forks_arr, (*config)->philo_number);
    pthread_mutex_destroy(&(*config)->must_exit_mutex);
    pthread_mutex_destroy(&(*config)->print_mutex);
}
 void ft_stop_simulation(t_config **config)
 {
    int i;
    
    i = 0;
    t_philo *temp_philo;
    temp_philo = (*config)->philo_list;

    while (i < (*config)->philo_number)
    {
        pthread_join(temp_philo->philo_thread, NULL);
        temp_philo = temp_philo->next;
        i++;
    }
    pthread_join((*config)->simulation_tracker_thread, NULL);
    ft_destroy_simultion(config);
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
    int     i;
    t_philo *temp_philo;

    i = 0;
    temp_philo = (*config)->philo_list;
    while (i < (*config)->philo_number)
    {
       if (pthread_create(&(temp_philo->philo_thread), NULL, &(ft_routine), temp_philo) != 0)
       {
            //TODO: terminate created threads
            ft_cleanup_threads((*config)->philo_list, temp_philo, config);
            return (2);
       }
        temp_philo = temp_philo->next;
        i++;
    }

    //svae launch time
    (*config)->initial_time = ft_get_now_stamp_mls();
    pthread_mutex_lock(&(*config)->simulation_syncher);
    (*config)->is_synchronized = true;
    pthread_mutex_unlock(&(*config)->simulation_syncher);

    return (0);
}

int ft_launch_simulation_tracker(t_config* config)
{
    if (pthread_create(&(config->simulation_tracker_thread), NULL, &(ft_track_simualtion), config) != 0)
    {
        ft_destroy_simultion(&config);
        return (4);
    }
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
    ft_launch_simulation_tracker(main_config);
    ft_stop_simulation(&main_config);
    return (0);
}