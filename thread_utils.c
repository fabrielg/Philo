/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:29:03 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/05 17:17:11 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_op(pthread_t *th, void *(*f)(void *), void *data, t_thread_op op)
{
	if (op == CREATE)
		return (pthread_create(th, NULL, f, data));
	else if (op == JOIN)
		return (pthread_join(*th, NULL));
	else if (op == DETACH)
		return (pthread_detach(*th));
	return (1);
}
