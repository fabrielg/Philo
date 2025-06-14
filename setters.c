/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:47:24 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/06/13 19:52:54 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(t_mutex *mutex, int *dest, int value)
{
	mutex_op(mutex, LOCK);
	*dest = value;
	mutex_op(mutex, UNLOCK);
}
void	set_long(t_mutex *mutex, long *dest, long value)
{
	mutex_op(mutex, LOCK);
	*dest = value;
	mutex_op(mutex, UNLOCK);
}
