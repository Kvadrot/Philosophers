/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:59:18 by ufo               #+#    #+#             */
/*   Updated: 2024/11/28 18:13:35 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include "../main_header.h"

void *ft_test_func(void *arg) {
    char *text = (char *)arg;  // Cast the argument back to char*
    printf("test : %s\n", text);
    return NULL;  // Thread function must return a void*
}

// int main(int argc, char **argv)
// {
//     pthread_t test_thread;
//     pthread_create(&test_thread, NULL, ft_test_func, "hello 123");
    
//     pthread_join(test_thread, NULL);

    
//     return (0);
// }