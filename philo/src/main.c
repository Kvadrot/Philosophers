/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:08:18 by ufo               #+#    #+#             */
/*   Updated: 2024/11/28 20:32:41 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

t_config *ft_init_config(char **argv)
{
    t_config   *config;

    config = malloc(sizeof(t_config) * 1);
    if (!config)
        return (NULL);
    config->philo_number = atoi(argv[1]);
    config->time_to_eat = atoi(argv[2]);
    config->time_to_die = atoi(argv[3]);
    config->time_to_sleep = atoi(argv[4]);
    if (argv[5])
        config->meals_number = atoi(argv[5]);
    else
        config->meals_number = 1;
    printf("LOG PRINT: philo_number = %d \n", config->philo_number);
    return(config);
}

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

int main(int argc, char **argv)
{
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
    ft_init_config(argv);
    return (0);
}