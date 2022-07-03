/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:45:05 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:10:35 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	f_init_pars(t_all *all, char **av, int ac)
{
	char	*inf;

	inf = "1";
	all->n_philo = ft_atoi(av[1], &inf);
	if (!inf)
		return (error(-1, all, 1));
	all->t_die = ft_atoi(av[2], &inf);
	if (!inf)
		return (error(-1, all, 1));
	all->t_meat = ft_atoi(av[3], &inf);
	if (!inf)
		return (error(-1, all, 1));
	all->t_sleep = ft_atoi(av[4], &inf);
	if (!inf)
		return (error(-1, all, 1));
	all->n_t = -1;
	if (ac == 6)
		all->n_t = ft_atoi(av[5], &inf);
	if (!inf)
		return (error(-1, all, 1));
	all->p_eat = 0;
	all->see = 0;
	return (f_init_mut(all));
}

long long	time_now(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	verif(t_all *all)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == all->n_philo)
			i = 0;
		pthread_mutex_lock(&all->check);
		if ((time_now() - all->philo[i].last_eat - all->t_zero) > all->t_die \
		&& (all->philo->n_t != 0))
		{
			all->see = 1;
			printf("%lli %i %s\n", time_now() - (all->t_zero), \
			all->philo->n_philo, "died");
			pthread_mutex_unlock(&all->check);
			break ;
		}
		if (all->p_eat == all->n_philo)
			break ;
		pthread_mutex_unlock(&all->check);
		i++;
	}
}

void	detach_potok(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->n_philo)
		pthread_join(all->philo[i].t, NULL);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac != 5 && ac != 6)
		return (error(-1, &all, 3));
	if (proverka_arguments(&all, av))
		return (1);
	if (f_init_pars(&all, av, ac))
		return (1);
	if (create_potok(&all) == 1)
		return (1);
	verif(&all);
	detach_potok(&all);
	free(all.forks);
	error(all.n_philo, &all, -1);
	return (0);
}
