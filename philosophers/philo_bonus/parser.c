/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:00:21 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:16:05 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->num_philo)
	{
		all->philo[i].id = i + 1;
		all->philo[i].last_eat = 0;
		all->philo[i].all = all;
	}
}

int	init_sem(t_all *all)
{
	all->philo = malloc(sizeof(t_ph) * all->num_philo);
	if (!all->philo)
		return (error(0, all, 2));
	clean_sem(all);
	all->msg = sem_open("msg", O_CREAT | O_EXCL, 0777, 1);
	all->forks = sem_open("forks", O_CREAT | O_EXCL, 0777, all->num_philo);
	all->died = sem_open("died", O_CREAT | O_EXCL, 0777, 1);
	init_philo(all);
	return (0);
}

int	ft_init_pars(t_all *all, char **av, int ac)
{
	char	*inf;

	inf = "1";
	all->num_philo = ft_atoi(av[1], &inf);
	if (!inf)
		return (error(0, all, 1));
	all->t_die = ft_atoi(av[2], &inf);
	if (!inf)
		return (error(0, all, 1));
	all->t_eat = ft_atoi(av[3], &inf);
	if (!inf)
		return (error(0, all, 1));
	all->t_sleep = ft_atoi(av[4], &inf);
	if (!inf)
		return (error(0, all, 1));
	all->num_eat = -1;
	if (ac == 6)
		all->num_eat = ft_atoi(av[5], &inf);
	if (!inf)
		return (error(0, all, 1));
	return (init_sem(all));
}
