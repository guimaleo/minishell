/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:54:02 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 21:54:12 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str)
{
	int		i;
	size_t	len;
	char	*ret;
	char	**split;

	ret = NULL;
	split = NULL;
	i = 0;
	len = ft_strlen(str);
	while (terminal()->env && terminal()->env[i])
	{
		if (!ft_strncmp(terminal()->env[i], str, len)
			&& terminal()->env[i][len] == '=')
			break ;
		i++;
	}
	if (terminal()->env && terminal()->env[i])
	{
		split = ft_split(terminal()->env[i], '=');
		if (split && split[1])
			ret = ft_strdup(split[1]);
		free_doubles((void **)split);
	}
	return (ret);
}

void	ft_check(void)
{
	int	i;

	i = 0;
	while (terminal()->input[i])
	{
		if (terminal()->input[i] == '|')
		{
			i++;
			while (ft_isspace(terminal()->input[i]))
				i++;
			if (terminal()->input[i] == '|')
				return ((void)ft_checkerror());
		}
		else
			i++;
	}
	i = 0;
	while (terminal()->input[i])
		i++;
	--i;
	while (ft_isspace(terminal()->input[i]))
		--i;
	if (terminal()->input[i] == '|')
		ft_checkerror();
}

void	ft_checkerror(void)
{
	printf("syntax error near unexpected token '|'\n");
	terminal()->stat = 2;
	free(terminal()->input);
	terminal()->input = NULL;
}
