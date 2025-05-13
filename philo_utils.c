/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:28:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:57:17 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"
#include <stdlib.h>

t_philo	new_philo(t_state state, int fork, int nb_eats)
{
	t_philo	philo;

	philo.state = state;
	philo.fork_taken = fork;
	philo.nb_eats = nb_eats;
	philo.id = 0;
	return (philo);
}

void	philos_update_id(t_list2 *philos)
{
	t_philo				*philo;
	unsigned char		index;

	index = 0;
	while (philos)
	{
		philo = (t_philo *)philos->content;
		philo->id = index;
		index++;
		philos = philos->next;
	}
}

void	display_philos(t_list2 *philos)
{
	t_list2	*temp;
	t_philo	*p;

	temp = philos;
	while (temp)
	{
		p = (t_philo *)temp->content;
		if (!p)
			break ;
		ft_printf("Philo[%03d]: state:%d, fork taken:%d, nb_eats:%d\n",
			p->id, p->state, p->fork_taken, p->nb_eats);
		temp = temp->next;
	}
}
