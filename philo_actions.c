/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 18:23:05 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/05 18:23:29 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
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
	if (philo->table->nb_philos % 2 == 0)
		return ;
	time_to_eat = philo->table->time_to_eat;
	time_to_sleep = philo->table->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	usleep_strict(time_to_think * 1e3, philo->table);
}
