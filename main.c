/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:32:44 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/16 02:59:01 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"

int	main(int argc, char *argv[])
{
	t_project	project;

	if (!(5 <= argc && argc <= 6))
	{
		ft_putstr_fd("Usage: ./philo <number_of_philosophers> ", 2);
		ft_putstr_fd("<time_to_die> <time_to_eat> <time_to_sleep> ", 2);
		ft_putendl_fd("[number_of_times_each_philosopher_must_eat]", 2);
		return (0);
	}
	if (!parsing(&project, argc, argv))
		return (ft_putendl_fd("Error while parsing arguments.", 2), 0);
	ft_lstclear2(&project.philos, free);
	return (0);
}
