/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ryuk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 15:22:04 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/04 14:55:44 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_thread_running(t_mutex *mtx, int threads, int nb_philos)
{
	int	result;

	result = 0;
	mutex_op(mtx, LOCK);
	if (threads == nb_philos)
		result = 1;
	mutex_op(mtx, UNLOCK);
	return (result);
}

static int	philo_died(t_philo *p)
{
	long	elapsed;
	long	time_to_die;

	if (get_int(&p->philo_access, &p->full))
		return (0);
	elapsed = get_time(MILLISECOND) - get_long(&p->philo_access, &p->last_eat);
	time_to_die = p->table->time_to_die;
	if (elapsed >= time_to_die)
		return (1);
	return (0);
}

void	*wait_for_death(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_thread_running(&table->table_access,
			table->nb_threads_ready, table->nb_philos))
			usleep_strict(1 * 1e3, table);
	while (!is_simulation_finished(table))
	{
		i = -1;
		while (++i < table->nb_philos && !is_simulation_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				print_state(DIED, table->philos + i);
				set_int(&table->table_access, &table->stop_simulation, 1);
			}
		}
		usleep_strict(1 * 1e3, table);
	}
	return (NULL);
}
