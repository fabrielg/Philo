/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:05 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/30 20:24:47 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./libft/libft.h"
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING
}	t_state;

typedef enum e_mtx_op
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
}	t_mtx_op;

typedef enum e_thread_op
{
	CREATE,
	JOIN,
	DETACH
}	t_thread_op;

typedef struct s_fork
{
	int		id;
	t_mutex	fork;
}	t_fork;

struct s_philo
{
	unsigned char	id;
	t_state			state;
	t_fork			*right_fork;
	t_fork			*left_fork;
	int				nb_eats;
	long			last_eat;
	pthread_t		thread;
	t_table			*table;
};

struct s_table
{
	int		nb_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eats_before_stop;
	long	start_simulation;
	int		stop_simulation;
	t_fork	*forks;
	t_philo	*philos;
};

int		parsing(t_table *project, int argc, char *argv[]);
void	clear_table(t_table *table);
void	error_exit(int error);
void	display_philos(t_philo *philos, int nb_philo);
void	mutex_op(t_mutex *mtx, t_mtx_op op);
void	thread_op(pthread_t *t, void *(*f)(void *), void *data, t_thread_op op);

#endif
