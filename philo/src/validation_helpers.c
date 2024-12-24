/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:38:54 by ufo               #+#    #+#             */
/*   Updated: 2024/12/24 16:30:08 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/main_header.h"



void    ft_print_default_input_error_number(void)
{
    printf("reminder: pls provide following args in propper sequence;\n");
    printf("philo_number\n time_to_eat\n time_to_die\n time_to_sleep\n meals_number\n");
}

bool	ft_isdigit(int someInt)
{
	if (someInt >= '0' && someInt <= '9')
		return (true);
	else
		return (false);
}

bool    ft_validate_input(char **argv)
{
    int i;
    int counter;
    counter = 0;
    i = 1;
    while (argv[i])
    {
        while (argv[i][counter])
        {
            if (ft_isdigit(argv[i][counter]) == false)
                return (false);
            counter++;
        }
        counter = 0;
        i++;
    }
    return (true);
}