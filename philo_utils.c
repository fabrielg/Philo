/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:28:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/03 18:09:05 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"
#include <stdlib.h>
#include <sys/time.h>

void	display_philos(t_philo *philos, int nb_philo)
{
	t_philo	p;
	int		i;

	i = -1;
	while (++i < nb_philo)
	{
		p = philos[i];
		ft_printf("Philo[%03d]: state:%d, fork left:[%d], ",
			p.id, p.state, p.left_fork->id, &p.left_fork->fork);
		ft_printf("fork right:[%d], nb_eats:%d, last eat:%d\n",
			p.right_fork->id, &p.right_fork->fork, p.nb_eats, p.last_eat);
	}
}

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
			usleep(usec / 2);
		else
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
	}
}

void	increase_threads_counts(t_table *table)
{
	mutex_op(&table->table_access, LOCK);
	table->nb_threads_ready++;
	mutex_op(&table->table_access, UNLOCK);
}
