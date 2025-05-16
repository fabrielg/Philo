/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:32:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/16 02:58:55 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "./libft/libft.h"

static int	get_args(t_project *project, int argc, char *argv[])
{
	if (!ft_atoi_strict(argv[1], &project->nb_philos))
		return (0);
	if (!ft_atoi_strict(argv[2], &project->time_to_die))
		return (0);
	if (!ft_atoi_strict(argv[3], &project->time_to_eat))
		return (0);
	if (!ft_atoi_strict(argv[4], &project->time_to_sleep))
		return (0);
	if (argc == 6 && !ft_atoi_strict(argv[5], &project->nb_eats_before_stop))
		return (0);
	else
		project->nb_eats_before_stop = -1;
	if (project->nb_philos < 1 || project->time_to_die < 0 \
		|| project->time_to_eat < 0 || project->time_to_sleep < 0)
		return (0);
	return (1);
}

static int	get_philos(t_project *project)
{
	unsigned char	id;
	t_philo			*p;
	t_list2			*node;

	id = 0;
	while (id < project->nb_philos)
	{
		p = new_philo(THINKING, 0, 0);
		if (!p)
			return (ft_lstclear2(&project->philos, free), 0);
		p->id = id;
		node = ft_lstnew2(p);
		if (!node)
			return (0);
		ft_lstadd_back2(&project->philos, node);
		id++;
	}
	return (1);
}

int	parsing(t_project *project, int argc, char *argv[])
{
	ft_memset(project, 0, sizeof(t_project));
	if (!get_args(project, argc, argv))
		return (0);
	if (!get_philos(project))
		return (0);
	return (1);
}
