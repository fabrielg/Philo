/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:28:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/06/13 20:20:07 by gfrancoi         ###   ########.fr       */
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
		ft_printf("Philo[%03d]: state:%d, fork right:[%d] %p,",
			p.id, p.state, p.right_fork->id, &p.right_fork->fork);
		ft_printf("fork left:[%d] %p, nb_eats:%d, last eat:%d\n",
			p.left_fork->id, &p.left_fork->fork, p.nb_eats, p.last_eat);
	}
}

int	is_simulation_finished(t_table *table)
{
	return (get_int(&table->table_access, &table->stop_simulation));
}

long	get_time(t_code_units unit)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit(-1);
	if (unit == SECOND)
		return (tv.tv_sec + (tv.usec / 1e6));
	else if (unit == MILLISECOND)
		return (tv.tv_sec * 1e3 + (tv.usec / 1e3));
	else if (unit == MICROSECOND)
		return (tv.tv_sec * 1e6 + tv.usec);
	return (-1);
}
