/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjanette <bjanette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:08:43 by bjanette          #+#    #+#             */
/*   Updated: 2022/06/17 21:30:53 by bjanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
