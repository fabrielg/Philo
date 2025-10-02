/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:05:47 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/04 20:31:34 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define LEFT_FORK "%ld %d has taken a fork\n"
#define RIGHT_FORK "%ld %d has taken a fork\n"
#define IS_EATING "%ld %d is eating\n"
#define IS_SLEEPING "%ld %d is sleeping\n"
#define IS_THINKING "%ld %d is thinking\n"
#define IS_DEAD "%ld %d died\n"

#define D_LEFT_FORK "[%6ld] %s%d takes the left fork	[🍴 - %d]\n"
#define D_RIGHT_FORK "[%6ld] %s%d takes the right fork\t[%d - 🍴]\n"
#define D_IS_EATING "[%6ld] %s%d is eating		[🍝 %d]\n"
#define D_IS_SLEEPING "[%6ld] %s%d is sleeping		[💤]\n"
#define D_IS_THINKING "[%6ld] %s%d is thinking		[🤔]\n"
#define D_IS_DEAD "[%6ld] %s%d died	[💀]\n"

static void	print_state_debug(t_state state, t_philo *philo)
{
	long	elapsed;

	mutex_op(&philo->table->print, LOCK);
	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (state == TAKE_LEFT_FORK && !is_simulation_finished(philo->table))
		printf(D_LEFT_FORK, elapsed, BLACK, philo->id, philo->left_fork->id);
	else if (state == TAKE_RIGHT_FORK && !is_simulation_finished(philo->table))
		printf(D_RIGHT_FORK, elapsed, BLACK, philo->id, philo->right_fork->id);
	else if (state == EATING && !is_simulation_finished(philo->table))
		printf(D_IS_EATING, elapsed, WHITE, philo->id, philo->nb_eats);
	else if (state == SLEEPING && !is_simulation_finished(philo->table))
		printf(D_IS_SLEEPING, elapsed, BLUE, philo->id);
	else if (state == THINKING && !is_simulation_finished(philo->table))
		printf(D_IS_THINKING, elapsed, CYAN, philo->id);
	else if (state == DIED && !is_simulation_finished(philo->table))
		printf(D_IS_DEAD, elapsed, RED, philo->id);
	printf("%s", RESET);
	mutex_op(&philo->table->print, UNLOCK);
}

void	print_state(t_state state, t_philo *philo)
{
	long	elapsed;

	if (DEBUG_MODE)
		return (print_state_debug(state, philo));
	mutex_op(&philo->table->print, LOCK);
	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (state == TAKE_LEFT_FORK && !is_simulation_finished(philo->table))
		printf(LEFT_FORK, elapsed, philo->id);
	else if (state == TAKE_RIGHT_FORK && !is_simulation_finished(philo->table))
		printf(RIGHT_FORK, elapsed, philo->id);
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
