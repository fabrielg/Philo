/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:05 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/13 18:32:36 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./libft/libft.h"

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING
}	t_state;

typedef struct s_philo	t_philo;
struct s_philo
{
	unsigned char	id;
	t_state			state;
	int				fork_taken;
	int				nb_eats;
};

typedef struct s_project
{
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eats_before_stop;
	t_list2	*philos;
}	t_project;

int		parsing(t_project *project, int argc, char *argv[]);
t_philo	new_philo(t_state state, int fork, int nb_eats);
void	philos_update_id(t_list2 *philos);
void	display_philos(t_list2 *philos);

#endif
