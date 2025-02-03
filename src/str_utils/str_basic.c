/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_basic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:47:15 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 12:20:17 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

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

	if (!s1 || !s2 || !n)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		len[2];
	int		i;

	if (!s2)
		return (NULL);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	ptr = ft_calloc((len[0] + len[1] + 1), sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[len[0] + i] = s2[i];
		i++;
	}
	return (ptr);
}

char	*ft_strjoin_char(char *s1, char *s2)
{
	char	*ptr;
	int		len[2];
	int		i;

	if (!s2)
		return (NULL);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	ptr = ft_calloc((len[0] + len[1] + 2), sizeof(char *));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '/';
	i = 0;
	while (s2[i])
	{
		ptr[len[0] + i +1] = s2[i];
		i++;
	}
	return (ptr);
}
