/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:28:19 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/30 17:28:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_op(t_mutex *mtx, t_mtx_op op)
{
	if (op == LOCK)
		pthread_mutex_lock(mtx);
	else if (op == UNLOCK)
		pthread_mutex_unlock(mtx);
	else if (op == INIT)
		pthread_mutex_init(mtx, NULL);
	else if (op == DESTROY)
		pthread_mutex_destroy(mtx);
}
