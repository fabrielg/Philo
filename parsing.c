/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:32:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/03 14:46:38 by gfrancoi         ###   ########.fr       */
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
	table->nb_eats_before_stop = -1;
	if (argc == 6 && !ft_atoi_strict(argv[5], &table->nb_eats_before_stop))
		return (0);
	if (table->nb_philos < 1 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (0);
	return (1);
}

static void	assign_forks(t_philo *p, t_fork *forks, int position)
{
	int	nb_philos;

	nb_philos = p->table->nb_philos;
	p->left_fork = &forks[(position + 1) % nb_philos];
	p->right_fork = &forks[position];
	if (p->id % 2 == 0)
	{
		p->left_fork = &forks[position];
		p->right_fork = &forks[(position + 1) % nb_philos];
	}
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
		p->full = 0;
		p->state = THINKING;
		p->last_eat = -1;
		p->table = table;
		mutex_op(&p->philo_access, INIT);
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
	mutex_op(&table->print, INIT);
	return (1);
}
