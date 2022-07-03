/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 22:15:20 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/20 22:26:50 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (c >= 48 && c <= 57);
	return (0);
}

long int	ft_dyp(long int k, char **inf)
{
	if (k > INT_MAX || k < INT_MIN)
	{
		*inf = NULL;
		return (-1);
	}
	return (k);
}

int	ft_atoi(const char *str, char **inf)
{
	long int	res;
	int			negative;

	negative = 1;
	res = 0;
	while (*str && (*str == ' ' || *str == '\n' \
	|| *str == '\t' || *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		negative = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= 48 && *str <= 57)
	{
		res = res * 10 + (*str - 48);
		if (ft_isdigit(*str) == 0)
		{
			*inf = NULL;
			return (0);
		}
		++str;
	}
	return (ft_dyp(res * negative, inf));
}

int	error(int i, t_all *all, int flag)
{
	if (flag == 0)
		printf("Error: mutex_init did not work\n");
	if (flag == 1)
		printf("Error: You entered a large number\n");
	if (flag == 2)
		printf("Error: Not allocated malloc\n");
	if (flag == 3)
		printf("Error: Incorrect number of arguments\n");
	if (flag == 4)
		printf("Error: A stream was not created\n");
	if (i != -1)
		clean_mutex(i, all);
	return (1);
}

int	create_potok2(t_all *all)
{
	int	i;

	i = 1;
	while (i < all->n_philo)
	{
		if (pthread_create(&all->philo[i].t, NULL, philo_make, &all->philo[i]))
		{
			free(all->forks);
			return (error(i, all, 4));
		}
		i += 2;
	}
	return (0);
}
