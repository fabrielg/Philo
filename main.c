/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:32:44 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/30 20:24:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"

void	error_exit(int error)
{
	if (error == 0)
	{
		ft_putstr_fd("Usage: ./philo <number_of_philosophers> ", 2);
		ft_putstr_fd("<time_to_die> <time_to_eat> <time_to_sleep> ", 2);
		ft_putendl_fd("[number_of_times_each_philosopher_must_eat]", 2);
	}
	exit(0);
}

void	clear_table(t_table *table)
{
	if (table && table->philos)
		free(table->philos);
	if (table && table->forks)
		free(table->forks);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!(5 <= argc && argc <= 6))
		error_exit(0);
	if (!parsing(&table, argc, argv))
		return (ft_putendl_fd("Error while parsing arguments.", 2), 0);
	clear_table(&table);
	return (0);
}
