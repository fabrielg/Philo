/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:37:00 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/04 23:09:15 by gfrancoi         ###   ########.fr       */
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
	usleep_strict(table->time_to_eat * 1e3, table);
	if (table->nb_eats_before_stop > 0
		&& philo->nb_eats >= table->nb_eats_before_stop)
		set_int(&philo->philo_access, &philo->full, 1);
	mutex_op(&philo->left_fork->fork, UNLOCK);
	mutex_op(&philo->right_fork->fork, UNLOCK);
}

void	thinking(t_philo *philo, int pre_simulation)
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_think;

	if (!pre_simulation)
		print_state(THINKING, philo);
	if (philo->table->nb_eats_before_stop % 2 == 0)
		return ;
	time_to_eat = philo->table->time_to_eat;
	time_to_sleep = philo->table->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	usleep_strict(time_to_think, philo->table);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_access, &philo->last_eat, get_time(MILLISECOND));
	increase_threads_counts(philo->table);
	desync_philos(philo);
	while (!all_thread_running(&philo->table->table_access,
			philo->table->nb_threads_ready, philo->table->nb_philos))
		;
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
	wait_all_threads(p->table);
	set_long(&p->philo_access, &p->last_eat, get_time(MILLISECOND));
	increase_threads_counts(p->table);
	print_state(TAKE_LEFT_FORK, p);
	while (!is_simulation_finished(p->table))
		usleep(200);
	return (NULL);
}

void	dinner_time(t_table *table)
{
	int	i;

	i = -1;
	if (table->nb_eats_before_stop == 0)
		return ;
	else if (table->nb_philos == 1)
		thread_op(&table->philos[0].thread, one_philo,
			&table->philos[0], CREATE);
	else
	{
		while (++i < table->nb_philos)
			thread_op(&table->philos[i].thread, dinner_simulation,
				&table->philos[i], CREATE);
	}
	thread_op(&table->ryuk, wait_for_death, table, CREATE);
	table->start_simulation = get_time(MILLISECOND);
	set_int(&table->table_access, &table->all_threads_ready, 1);
	i = -1;
	while (++i < table->nb_philos)
		thread_op(&table->philos[i].thread, NULL, NULL, JOIN);
	if (DEBUG_MODE && !get_int(&table->table_access, &table->stop_simulation))
		printf(GREEN_B"All philosophers have eaten %d times 🎉\n"RESET,
			table->nb_eats_before_stop);
	set_int(&table->table_access, &table->stop_simulation, 1);
	thread_op(&table->ryuk, NULL, NULL, JOIN);
}
