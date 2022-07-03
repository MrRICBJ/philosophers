/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:43:24 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/21 15:14:59 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/stat.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/errno.h>
# include <signal.h>

typedef struct s_ph	t_ph;

typedef struct s_all
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_eat;
	long long int	t_zero;
	t_ph			*philo;
	sem_t			*msg;
	sem_t			*forks;
	sem_t			*died;
}	t_all;

typedef struct s_ph
{
	int				id;
	long long int	last_eat;
	pid_t			pid;
	pthread_t		t;
	t_all			*all;
}	t_ph;

int			proverka_arguments(char **av);
int			ft_atoi(const char *str, char **inf);
int			error(int i, t_all *all, int flag);
int			create_proc(t_all *all);
long long	time_now(void);
int			ft_init_pars(t_all *all, char **av, int ac);
int			ft_isdigit(int c);
char		*ft_itoa(int nbr);
void		f_time(long long int time);
void		clean_sem(t_all *all);
#endif
