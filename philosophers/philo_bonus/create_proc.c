/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 21:03:01 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:19:25 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	f_do(t_all	*all, char *s, int id)
{
	sem_wait(all->msg);
	printf("%lli %i %s\n", time_now() - all->t_zero, id, s);
	sem_post(all->msg);
}

void	eat_ph(t_ph *philo, t_all *all)
{
	sem_wait(all->forks);
	f_do(all, "has taken a fork", philo->id);
	sem_wait(all->forks);
	f_do(all, "has taken a fork", philo->id);
	sem_wait(philo->all->died);
	f_do(all, "is eating", philo->id);
	philo->last_eat = time_now() - all->t_zero;
	sem_post(philo->all->died);
	f_time(all->t_eat);
	sem_post(all->forks);
	sem_post(all->forks);
}

void	*philo_make(void *ph)
{
	t_all	*all;
	t_ph	*philo;

	philo = (t_ph *)ph;
	all = philo->all;
	while (all->num_eat)
	{
		eat_ph(philo, all);
		f_do(all, "is sleeping", philo->id);
		f_time(all->t_sleep);
		f_do(all, "is thinking", philo->id);
		if (all->num_eat > 0)
			(all->num_eat)--;
	}
	return (0);
}

void	verif(t_ph *philo)
{
	int	i;

	i = 0;
	while (philo->all->num_eat)
	{
		sem_wait((philo)->all->died);
		if ((time_now() - philo->last_eat - philo->all->t_zero) \
		> philo->all->t_die)
		{
			sem_wait((philo)->all->msg);
			printf("%lli %i %s\n", time_now() - (philo)->all->t_zero, \
			(philo)->id, "died");
			exit(1);
		}
		sem_post((philo)->all->died);
	}
	exit (0);
}

int	create_proc(t_all *all)
{
	int	i;

	all->t_zero = time_now();
	i = -1;
	while (++i < all->num_philo)
	{
		all->philo[i].pid = fork();
		if (all->philo[i].pid == -1)
			exit(1);
		if (all->philo[i].pid == 0)
		{
			if (all->philo[i].id % 2 == 0)
				f_time(200);
			if (pthread_create(&all->philo[i].t, NULL, philo_make, \
			&all->philo[i]))
				return (error(1, all, 4));
			pthread_detach(all->philo[i].t);
			usleep(200);
			verif(&all->philo[i]);
		}
	}
	return (0);
}
