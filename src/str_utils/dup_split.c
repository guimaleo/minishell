/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:21 by lede-gui          #+#    #+#             */
/*   Updated: 2024/10/25 12:54:46 by lede-gui         ###   ########.fr       */
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

	// count = (str[0] != c);
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

char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	int		wc;
	int		end;
	char	**split;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	wc = ft_countwords(str, c);
	split = (char **)ft_calloc(wc + 1, sizeof(char *));
	while (str[i])
	{
		while (str[i] == c)
			i++;
		end = 0;
		while (str[end + i] && str[end + i] != c)
			end++;
		split[j] = ft_strndup(str + i, end); //seg fault! test: minishell $> cat Makefile
		/*Program received signal SIGSEGV, Segmentation fault.
			ft_split (str=0x555555595e70 "cat Makefile ", c=32 ' ') at src/str_utils/dup_split.c:101
			101			split[j] = ft_strndup(str + i, end);
			(gdb)
		*/
		j++;
		i += end;
	}
	return (split);
}




// int	ft_countwords(char *str, char c)
// {
// 	int	count;
// 	int	i;

// 	count = (str[0] != c);
// 	i = 0;
// 	i++;
// 	while (str[i])
// 	{
// 		if (str[i] == c )
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// char	**ft_split(char *str, char c)
// {
// 	int		i;
// 	int		j;
// 	int		end;
// 	char	**split;

// 	i = 0;
// 	j = 0;
// 	if (!str || !str[0])
// 		return (NULL);
// 	split = (char **)ft_calloc(1, ft_countwords(str, c) + 1 * sizeof(char *));
// 	while (str[i])
// 	{
// 		while (str[i] == c)
// 			i++;
// 		end = 0;
// 		while (str[end + i] && str[end + i] != c)
// 			end++;
// 		split[j] = ft_strndup(str + i, end);
// 		j++;
// 		i += end;
// 	}
// 	return (split);
// }
