/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:29:03 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/30 17:29:26 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_op(pthread_t *th, void *(*f)(void *), void *data, t_thread_op op)
{
	if (op == CREATE)
		pthread_create(th, NULL, f, data);
	else if (op == JOIN)
		pthread_join(*th, NULL);
	else if (op == DETACH)
		pthread_detach(*th);
}
