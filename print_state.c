/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:05:47 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/02 16:08:56 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_state state, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND);
	mutex_op(&philo->table->print, LOCK);
	if (state == TAKE_LEFT_FORK && !is_simulation_finished(philo->table))
		printf("%-6ld %d has taken the left fork\n", elapsed, philo->id);
	else if (state == TAKE_RIGHT_FORK && !is_simulation_finished(philo->table))
		printf("%-6ld %d has taken the right fork\n", elapsed, philo->id);
	else if (state == EATING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (state == SLEEPING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (state == THINKING && !is_simulation_finished(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (state == DIED && !is_simulation_finished(philo->table))
		printf("%-6ld %d died\n", elapsed, philo->id);
	mutex_op(&philo->table->print, UNLOCK);
}
