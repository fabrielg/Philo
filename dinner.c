/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:37:00 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/06/14 14:12:44 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->table);
	while (!is_simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);
		
	}
	return (NULL);
}

void	dinner_time(t_table *table)
{
	int	i;

	i = -1;
	if (table->nb_eats_before_stop == 0)
		return ;
	else if (table->nb_philos == 1)
		;	//TODO
	else
	{
		while (++i < table->nb_philos)
			thread_op(&table->philos[i].thread, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_simulation = get_time(MILLISECOND);
	set_int(&table->table_access, &table->wait_all_threads, 1);
	i = -1;
	while (++i < table->nb_philos)
		thread_op(&table->philos[i].thread, NULL, NULL, JOIN);
}
