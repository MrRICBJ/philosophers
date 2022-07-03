/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:42:37 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/21 15:14:38 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	time_now(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

void	ft_exit(t_all *all)
{
	int	pid;
	int	i;

	i = -1;
	while (++i < all->num_philo)
	{
		waitpid(-1, &pid, 0);
		if (pid)
		{
			i = -1;
			while (++i < all->num_philo)
				kill(all->philo[i].pid, 9);
			break ;
		}
	}
	free(all->philo);
	error(-1, all, -1);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac != 5 && ac != 6)
		return (error(0, &all, 3));
	if (proverka_arguments(av))
		return (error(0, &all, 3));
	if (ft_init_pars(&all, av, ac))
		return (1);
	if (create_proc(&all))
	{
		free(all.philo);
		return (error(0, &all, 3));
	}
	ft_exit(&all);
	return (0);
}
