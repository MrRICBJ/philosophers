/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_potok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:41:57 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:28:11 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f_do(t_ph	*philo, char *s, int id)
{
	pthread_mutex_lock(philo->msg);
	if (!(*philo->see))
		printf("%lli %i %s\n", time_now() - (*philo->t_zero), id, s);
	pthread_mutex_unlock(philo->msg);
}

void	f_time(long long int time, t_ph *philo)
{
	long long	i;

	(void)philo;
	i = time_now();
	while (1)
	{
		if ((time_now() - i) >= time)
			break ;
		usleep(100);
	}
}

int	eat_ph(t_ph *philo)
{
	pthread_mutex_lock(&philo->forks[philo->right]);
	f_do(philo, "has taken a fork", philo->n_philo);
	if (philo->num_ph == 1)
		return (1);
	pthread_mutex_lock(&philo->forks[philo->left]);
	f_do(philo, "has taken a fork", philo->n_philo);
	pthread_mutex_lock(philo->check);
	philo->last_eat = time_now() - (*philo->t_zero);
	pthread_mutex_unlock(philo->check);
	f_do(philo, "is eating", philo->n_philo);
	f_time(philo->t_meat, philo);
	pthread_mutex_unlock(&philo->forks[philo->left]);
	pthread_mutex_unlock(&philo->forks[philo->right]);
	return (0);
}

void	*philo_make(void *ph)
{
	t_ph	*philo;

	philo = (t_ph *)ph;
	while (philo->n_t && (*philo->see != 1))
	{
		if (eat_ph(philo))
			return ("1");
		f_do(philo, "is sleeping", philo->n_philo);
		f_time(philo->t_sleep, philo);
		f_do(philo, "is thinking", philo->n_philo);
		if (philo->n_t > 0)
			(philo->n_t)--;
		pthread_mutex_lock(philo->check);
		if (philo->n_t == 0)
			(*philo->p_eat)++;
		pthread_mutex_unlock(philo->check);
	}
	return (0);
}

int	create_potok(t_all *all)
{
	int	i;

	i = 0;
	all->t_zero = time_now();
	while (i < all->n_philo)
	{
		if (pthread_create(&(all->philo[i].t), NULL, philo_make, \
		&all->philo[i]))
		{
			free(all->forks);
			return (error(i, all, 4));
		}
		i += 2;
	}
	usleep(300);
	return (create_potok2(all));
}
