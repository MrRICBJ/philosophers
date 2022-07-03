/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:46:04 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:27:02 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_ph
{
	int				n_philo;
	int				t_die;
	int				t_meat;
	int				t_sleep;
	int				n_t;
	int				*p_eat;	
	int				*see;
	int				num_ph;
	long long int	*t_zero;
	long long int	last_eat;
	pthread_t		t;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;
	int				right;
	int				left;
	pthread_mutex_t	*check;
}	t_ph;

typedef struct s_all
{
	int				n_philo;
	int				t_die;
	int				t_meat;
	int				t_sleep;
	int				n_t;
	int				p_eat;
	int				see;
	long long int	t_zero;
	t_ph			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	check;
}	t_all;

int			ft_atoi(const char *str, char **inf);
int			error(int i, t_all *all, int flag);
long long	time_now(void);
int			ft_isdigit(int c);
int			f_init_mut(t_all *all);
void		f_init_philo(t_all *all);
int			create_potok(t_all *all);
void		*philo_make(void *ph);
long long	time_now(void);
int			proverka_arguments(t_all *all, char **av);
void		clean_mutex(int i, t_all *all);
int			create_potok2(t_all *all);

#endif
