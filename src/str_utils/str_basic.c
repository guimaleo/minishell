/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:47:15 by lede-gui          #+#    #+#             */
/*   Updated: 2024/10/24 22:47:48 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}
