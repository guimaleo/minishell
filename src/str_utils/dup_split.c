/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:21 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/17 23:27:05 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Duplicates a string until n characters
 *
 * @param str Source
 * @param n number of chars
 */
char	*ft_strndup(char *str, int n)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str) + 1;
	if (len > n)
		len = n;
	dup = (char *)ft_calloc(1, n + 1);
	if (!dup)
		return (NULL);
	while (str[i] && i < len)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*dup;

	i = 0;
	if (!str)
		return (NULL);
	dup = (char *)ft_calloc(1, ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

int	ft_countwords(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_rec_split(char *s, char **ret, char c, int count)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	while (*s == c)
		s++;
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (i)
		tmp = ft_calloc(1, i + 1);
	i = 0;
	while (tmp && *s && *s != c)
		tmp[i++] = *s++;
	if (tmp)
		ret = ft_rec_split(s, ret, c, count + 1);
	else
		ret = ft_calloc(count + 1, sizeof(char *));
	ret[count] = tmp;
	return (ret);
}

char	**ft_split(char *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_rec_split(s, NULL, c, 0));
}
