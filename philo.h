/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:33:05 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/07/04 15:10:26 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "./libft/libft.h"
# include <pthread.h>

# define DEBUG_MODE 1

typedef pthread_mutex_t	t_mutex;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef enum e_state
{
	EATING,
	THINKING,
	SLEEPING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED
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

typedef enum e_time_units
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_units;

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
	int				full;
	long			last_eat;
	pthread_t		thread;
	t_mutex			philo_access;
	t_table			*table;
};

struct s_table
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_eats_before_stop;
	long		start_simulation;
	int			stop_simulation;
	int			all_threads_ready;
	int			nb_threads_ready;
	t_fork		*forks;
	t_philo		*philos;
	pthread_t	ryuk;
	t_mutex		print;
	t_mutex		table_access;
};

/*		Main Functions		*/
int		parsing(t_table *project, int argc, char *argv[]);
void	clear_table(t_table *table);
int		error_exit(int error);
void	dinner_time(t_table *table);
void	*wait_for_death(void *data);

/*		Utils Functions		*/
void	display_philos(t_philo *philos, int nb_philo);
int		is_simulation_finished(t_table *table);
void	wait_all_threads(t_table *table);
long	get_time(t_time_units unit);
void	usleep_strict(long usec, t_table *table);
void	print_state(t_state state, t_philo *philo);
void	increase_threads_counts(t_table *table);
int		all_thread_running(t_mutex *mtx, int threads, int nb_philos);

/*		Mutex and Threads Operations		*/
void	mutex_op(t_mutex *mtx, t_mtx_op op);
void	thread_op(pthread_t *t, void *(*f)(void *), void *data, t_thread_op op);

/*		Getters and Setters		*/
int		get_int(t_mutex *mutex, int *value);
void	set_int(t_mutex *mutex, int *dest, int value);
long	get_long(t_mutex *mutex, long *value);
void	set_long(t_mutex *mutex, long *dest, long value);

#endif
