/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:37:00 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/02 16:02:17 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	mutex_op(&philo->left_fork->fork, LOCK);
	print_state(TAKE_LEFT_FORK, philo);
	mutex_op(&philo->right_fork->fork, LOCK);
	print_state(TAKE_RIGHT_FORK, philo);
	set_long(&philo->philo_access, &philo->last_eat, get_time(MILLISECOND));
	philo->nb_eats++;
	print_state(EATING, philo);
	usleep_strict(table->time_to_eat, table);
	if (table->nb_eats_before_stop > 0
		&& philo->nb_eats == table->nb_eats_before_stop)
		set_int(&philo->philo_access, &philo->full, 1);
	mutex_op(&philo->left_fork->fork, UNLOCK);
	mutex_op(&philo->right_fork->fork, UNLOCK);
}

static void	thinking(t_philo *philo)
{
	print_state(THINKING, philo);
}

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
		print_state(SLEEPING, philo);
		usleep_strict(philo->table->time_to_sleep, philo->table);
		thinking(philo);
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
	set_int(&table->table_access, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->nb_philos)
		thread_op(&table->philos[i].thread, NULL, NULL, JOIN);
}
