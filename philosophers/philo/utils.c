/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:35:40 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:23:58 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	proverka_arguments(t_all *all, char **av)
{
	int		i;
	int		j;
	char	*c;

	i = 1;
	c = "1";
	while (av[i])
	{
		if (ft_atoi(av[i], &c) < 1)
			return (error(-1, all, 3));
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j++]))
				return (error(-1, all, 3));
		}
		i++;
	}
	return (0);
}

void	clean_mutex(int i, t_all *all)
{
	free(all->philo);
	pthread_mutex_destroy(&all->check);
	if (i > 0)
	{
		while (--i > -1)
			pthread_mutex_destroy(&all->forks[i]);
	}
}

int	init_forks(t_all *all)
{
	int	i;

	all->forks = malloc (sizeof(pthread_mutex_t) * all->n_philo);
	if (!(all->forks))
		return (error(-2, all, 2));
	i = -1;
	while (++i < all->n_philo)
	{
		if (pthread_mutex_init(&all->forks[i], NULL))
		{
			free(all->forks);
			return (error(i, all, 0));
		}
	}
	return (0);
}

int	f_init_mut(t_all *all)
{
	int	i;

	i = -1;
	all->philo = malloc (sizeof(t_ph) * all->n_philo);
	if (!(all->philo))
		return (error(-1, all, 2));
	if (pthread_mutex_init(&all->message, NULL))
		return (error(-2, all, 0));
	if (pthread_mutex_init(&all->check, NULL))
		return (error(-2, all, 0));
	if (init_forks(all))
		return (1);
	f_init_philo(all);
	return (0);
}

void	f_init_philo(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
	{
		all->philo[i].n_philo = i + 1;
		all->philo[i].t_die = all->t_die;
		all->philo[i].t_meat = all->t_meat;
		all->philo[i].t_sleep = all->t_sleep;
		all->philo[i].n_t = all->n_t;
		all->philo[i].see = &all->see;
		all->philo[i].msg = &all->message;
		all->philo[i].check = &all->check;
		all->philo[i].t_zero = &all->t_zero;
		all->philo[i].last_eat = 0;
		all->philo[i].num_ph = all->n_philo;
		all->philo[i].p_eat = &all->p_eat;
		all->philo[i].right = all->philo[i].n_philo - 1;
		all->philo[i].forks = all->forks;
		if (i + 1 == all->n_philo)
			all->philo[i].left = 0;
		else
			all->philo[i].left = all->philo[i].n_philo;
	}
}
