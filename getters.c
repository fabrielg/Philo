/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:47:01 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/06/13 19:52:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_int(t_mutex *mutex, int *value)
{
	int	result;

	mutex_op(mutex, LOCK);
	result = *value;
	mutex_op(mutex, UNLOCK);
	return (result);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	result;

	mutex_op(mutex, LOCK);
	result = *value;
	mutex_op(mutex, UNLOCK);
	return (result);
}
