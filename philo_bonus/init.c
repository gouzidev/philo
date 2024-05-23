/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:42 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 03:47:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verify(t_data *data, int ac)
{
	if (!data)
		return (0);
    if (data->nthreads > 200 || data->nthreads < 1)
        return 0;
    if (data->n_eat_times < 1 && ac == 6)
        return 0;
    if (data->time_to_die < 60)
        return 0;
    if (data->time_to_eat < 60)
        return 0;
    if (data->time_to_sleep < 60)
        return 0;
    return 1;
    
}
