/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ufo <ufo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:36:10 by ufo               #+#    #+#             */
/*   Updated: 2024/12/24 14:46:39 by ufo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../main_header.h"

// @MARK: get_elapsed_time
// =================================================================================
// Descritption: 
//      returns current time_stamp in mls (long long)
// How_it_works:
// =================================================================================
//
long long	ft_get_now_stamp_mls(void)
{
	struct timeval			tv;

	if (gettimeofday(&tv, NULL) == 0)
		return (((tv.tv_sec) * (unsigned int)1000) + ((tv.tv_usec) / 1000));
	else
		return (0);
}

// @MARK: get_elapsed_time
// =================================================================================
// Descritption: 
//      Calculates elapsed time from given time
// How_it_works:
// =================================================================================
//
long long ft_get_elapsed_time(long long start_time)
{
    long long   now;

    now = ft_get_now_stamp_mls();
    return (now - start_time);
}
