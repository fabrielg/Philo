/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:32:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/06/13 19:48:56 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"

static int	get_args(t_table *table, int argc, char *argv[])
{
	if (!ft_atoi_strict(argv[1], &table->nb_philos))
		return (0);
	if (!ft_atoi_strict(argv[2], &table->time_to_die))
		return (0);
	if (!ft_atoi_strict(argv[3], &table->time_to_eat))
		return (0);
	if (!ft_atoi_strict(argv[4], &table->time_to_sleep))
		return (0);
	if (argc == 6 && !ft_atoi_strict(argv[5], &table->nb_eats_before_stop))
		return (0);
	else
		table->nb_eats_before_stop = -1;
	if (table->nb_philos < 1 || table->time_to_die < 0 \
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (0);
	return (1);
}

static void	assign_forks(t_philo *p, t_fork *forks, int position)
{
	p->right_fork = &forks[(position + 1) % p->table->nb_philos];
	p->left_fork = &forks[position];
}

static int	init_philos(t_table *table)
{
	unsigned char	id;
	t_philo			*p;

	table->philos = malloc(table->nb_philos * sizeof(t_philo));
	if (!table->philos)
		return (0);
	id = 0;
	while (id < table->nb_philos)
	{
		p = table->philos + id;
		p->id = id + 1;
		p->nb_eats = 0;
		p->state = THINKING;
		p->last_eat = -1;
		p->table = table;
		assign_forks(p, table->forks, id);
		id++;
	}
	return (1);
}

static int	get_forks(t_table *table)
{
	int	i;

	table->forks = malloc(table->nb_philos * sizeof(t_fork));
	if (!table->forks)
		return (0);
	i = -1;
	while (++i < table->nb_philos)
	{
		mutex_op(&table->forks[i].fork, INIT);
		table->forks[i].id = i;
	}
	return (1);
}

int	parsing(t_table *table, int argc, char *argv[])
{
	ft_memset(table, 0, sizeof(t_table));
	if (!get_args(table, argc, argv))
		return (0);
	if (!get_forks(table))
		return (0);
	if (!init_philos(table))
		return (0);
	mutex_op(&table->table_access, INIT);
	return (1);
}
