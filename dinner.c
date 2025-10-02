/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:37:00 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/05 18:51:15 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_start(philo->table->start_simulation);
	set_long(&philo->philo_access, &philo->last_eat, get_time(MILLISECOND));
	desync_philos(philo);
	while (!is_simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		print_state(SLEEPING, philo);
		usleep_strict(philo->table->time_to_sleep * 1e3, philo->table);
		thinking(philo, 0);
	}
	return (NULL);
}

static void	*one_philo(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	wait_start(p->table->start_simulation);
	set_long(&p->philo_access, &p->last_eat, get_time(MILLISECOND));
	print_state(TAKE_LEFT_FORK, p);
	while (!is_simulation_finished(p->table))
		usleep(200);
	return (NULL);
}

static int	create_threads(t_table *table)
{
	int	i;

	if (table->nb_philos == 1)
	{
		if (thread_op(&table->philos[0].thread, one_philo,
				&table->philos[0], CREATE))
			return (0);
	}
	else
	{
		i = -1;
		while (++i < table->nb_philos)
		{
			if (thread_op(&table->philos[i].thread, dinner_simulation,
					&table->philos[i], CREATE))
				return (0);
		}
	}
	if (thread_op(&table->ryuk, wait_for_death, table, CREATE))
		return (0);
	return (1);
}

int	dinner_time(t_table *table)
{
	int	i;

	if (table->nb_eats_before_stop == 0)
		return (1);
	table->start_simulation = get_time(MILLISECOND) + (table->nb_philos * 20);
	if (!create_threads(table))
		return (0);
	i = -1;
	while (++i < table->nb_philos)
	{
		if (thread_op(&table->philos[i].thread, NULL, NULL, JOIN))
			return (0);
	}
	if (DEBUG_MODE && !get_int(&table->table_access, &table->stop_simulation))
		printf(GREEN_B"All philosophers have eaten %d times 🎉\n"RESET,
			table->nb_eats_before_stop);
	set_int(&table->table_access, &table->stop_simulation, 1);
	if (thread_op(&table->ryuk, NULL, NULL, JOIN))
		return (0);
	return (1);
}
