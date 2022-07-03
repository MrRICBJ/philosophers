/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:54:30 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/21 15:14:45 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c >= 48 && c <= 57);
	return (0);
}

int	proverka_arguments(char **av)
{
	int		i;
	int		j;
	char	*c;

	i = 1;
	c = "1";
	while (av[i])
	{
		if (ft_atoi(av[i], &c) < 1)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j++]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	clean_sem(t_all *all)
{
	sem_close(all->msg);
	sem_close(all->died);
	sem_close(all->forks);
	sem_unlink("msg");
	sem_unlink("forks");
	sem_unlink("died");
}

int	error(int i, t_all *all, int flag)
{
	if (flag == 0)
		printf("Error: sem_init did not work\n");
	if (flag == 1)
		printf("Error: You entered a large number\n");
	if (flag == 2)
		printf("Error: Not allocated malloc\n");
	if (flag == 3)
		printf("Error: Incorrect number of arguments\n");
	if (flag == 4)
		printf("Error: A stream was not created\n");
	if (i != 0)
		clean_sem(all);
	return (1);
}

void	f_time(long long int time)
{
	long long	i;

	i = time_now();
	while (1)
	{
		if ((time_now() - i) >= time)
			break ;
		usleep(100);
	}
}
