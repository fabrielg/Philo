/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:28:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/04 23:05:17 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <sys/time.h>

int	is_simulation_finished(t_table *table)
{
	return (get_int(&table->table_access, &table->stop_simulation));
}

long	get_time(t_time_units unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit(-1);
	if (unit == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (unit == MILLISECOND)
		return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
	else if (unit == MICROSECOND)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	return (-1);
}

void	usleep_strict(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (is_simulation_finished(table))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	desync_philos(t_philo *philo)
{
	if (philo->table->nb_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep_strict(3e4, philo->table);
	}
	else if (philo->id % 2)
		thinking(philo, 1);
}
