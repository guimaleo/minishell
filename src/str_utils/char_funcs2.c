/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_funcs2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:24:25 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/17 23:24:53 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isupper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

static int	dig_count(int nb)
{
	int		dig;

	dig = 0;
	if (nb < 1)
		dig++;
	while (nb)
	{
		dig++;
		nb /= 10;
	}
	return (dig);
}

char	*ft_itoa(int nb)
{
	char	*res;
	int		dig;

	dig = dig_count(nb);
	res = ft_calloc(dig + 1, 1);
	if (!res)
		return (NULL);
	if (nb == 0)
		res[0] = '0';
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			res = "-2147483648\0";
			return (res);
		}
		res[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		res[--dig] = (nb % 10) + 48;
		nb /= 10;
	}
	return (res);
}
