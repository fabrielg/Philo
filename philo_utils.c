/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:28:39 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/30 20:29:24 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"
#include <stdlib.h>

void	display_philos(t_philo *philos, int nb_philo)
{
	t_philo	p;
	int		i;

	i = -1;
	while (++i < nb_philo)
	{
		p = philos[i];
		ft_printf("Philo[%03d]: state:%d, fork right:[%d] %p,",
			p.id, p.state, p.right_fork->id, &p.right_fork->fork);
		ft_printf("fork left:[%d] %p, nb_eats:%d, last eat:%d\n",
			p.left_fork->id, &p.left_fork->fork, p.nb_eats, p.last_eat);
	}
}
