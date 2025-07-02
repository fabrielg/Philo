/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:05:47 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/02 16:38:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define LEFT_FORK "[%-6ld]"BLACK" %d has taken the left fork\n"RESET
#define RIGHT_FORK "[%-6ld]"BLACK" %d has taken the right fork\n"RESET
#define IS_EATING "[%-6ld]"WHITE" %d is eating\n"RESET
#define IS_SLEEPING "[%-6ld]"BLUE" %d is sleeping\n"RESET
#define IS_THINKING "[%-6ld]"CYAN" %d is thinking\n"RESET
#define IS_DEAD "[%-6ld]"RED" %d died\n"RESET

void	print_state(t_state state, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND);
	mutex_op(&philo->table->print, LOCK);
	if (state == TAKE_LEFT_FORK && !is_simulation_finished(philo->table))
		printf(RIGHT_FORK, elapsed, philo->id);
	else if (state == TAKE_RIGHT_FORK && !is_simulation_finished(philo->table))
		printf(LEFT_FORK, elapsed, philo->id);
	else if (state == EATING && !is_simulation_finished(philo->table))
		printf(IS_EATING, elapsed, philo->id);
	else if (state == SLEEPING && !is_simulation_finished(philo->table))
		printf(IS_SLEEPING, elapsed, philo->id);
	else if (state == THINKING && !is_simulation_finished(philo->table))
		printf(IS_THINKING, elapsed, philo->id);
	else if (state == DIED && !is_simulation_finished(philo->table))
		printf(IS_DEAD, elapsed, philo->id);
	mutex_op(&philo->table->print, UNLOCK);
}
