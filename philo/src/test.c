/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:59:18 by ufo               #+#    #+#             */
/*   Updated: 2024/12/04 12:36:10 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include "../main_header.h"

typedef struct s_test {
    int i;
    pthread_mutex_t mutex;
} t_test;

void *incrementor_counter(void *arg)
{
    t_test *test_data;
    test_data = (t_test *)arg;
    for (int j = 0; j < 5; j++) {
        // Lock the mutex before modifying the shared resource
        pthread_mutex_lock(&(test_data->mutex));
        test_data->i++;
        printf("Thread incremented counter to %d\n", test_data->i);
        // Unlock the mutex after modification
        pthread_mutex_unlock(&(test_data->mutex));

        // Simulate some work
        usleep(100000); // 100 ms
    }

    return (NULL);
}


// int main(int argc, char **argv)
// {
//     t_test *test_data;
//     pthread_t test_thread[2];
//     test_data = malloc(sizeof(t_test));
//     pthread_mutex_init(&(test_data->mutex), NULL);
//     pthread_create(&test_thread[0], NULL, incrementor_counter, test_data);
//     pthread_create(&test_thread[1], NULL, incrementor_counter, test_data);

    
    
//     pthread_join(test_thread[0], NULL);
//     pthread_join(test_thread[1], NULL);
//     pthread_mutex_destroy(&(test_data->mutex));

    
//     return (0);
// }