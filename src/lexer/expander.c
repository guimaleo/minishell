/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:36:31 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/11 19:44:48 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Takes the input and injects the value into any of the passed variables
 * preffixed with a '$'
 */
char	*inject_expansion(char *input, char *key, char *value)
{
	size_t		len;
	size_t		i;
	size_t		j;
	size_t		r;
	char		*str[2];

	len = ft_strlen(input) + ft_strlen(value);
	str[0] = ft_calloc(len + 1, 1);
	i = check_char(input, '$') + 1;
	j = 0;
	while (j < i && *input != '$')
		str[0][j++] = *(input)++;
	input++;
	while (*(key++))
		input++;
	r = 0;
	while (value[r])
		str[0][j++] = value[r++];
	while (j < len && *input)
		str[0][j++] = *(input)++;
	str[1] = ft_strdup(str[0]);
	return (free(str[0]), str[1]);
}

static char	*key_extractor(char *arg, int *pos)
{
	int		start;
	int		len;
	char	*key;
	char	*tmp;

	start = *pos;
	while (arg[*pos] && ft_isupper(arg[*pos]))
		(*pos)++;
	while (arg[*pos] && !ft_isspace(arg[*pos]) && \
		arg[*pos] != '\"' && arg[*pos] != '\'')
		(*pos)++;
	len = *pos - start;
	key = ft_substr(arg, start, len);
	tmp = ft_getenv(key);
	if (key && tmp)
		return (free(tmp), key);
	free(key);
	return (NULL);
}

static char	*find_value(char *key, int len)
{
	char	*env_value;
	char	*value;
	char	*copy;

	copy = ft_strndup(key, len);
	if (!copy)
		return (NULL);
	env_value = ft_getenv(copy);
	free(copy);
	if (env_value)
	{
		value = ft_strdup(env_value);
		return (free(env_value), value);
	}
	return (NULL);
}

char	*check_variable(t_cmd *cmd, int *i, int *pos)
{
	char	*key;
	char	*value;
	char	*expanded;

	key = key_extractor(cmd->args[*i], pos);
	if (!key)
	{
		free(cmd->args[*i]);
		return (ft_strdup(""));
	}
	value = find_value(key, ft_strlen(key));
	if (!value)
	{
		if (key)
			free(key);
		free(value);
		free(cmd->args[*i]);
		return (NULL);
	}
	expanded = inject_expansion(cmd->args[*i], key, value);
	return (free(key), free(value), free(cmd->args[*i]), expanded);
}

void	expansions(t_cmd *cmd)
{
	int		i;
	int		pos;
	char	*tmp;

	while (cmd)
	{
		i = -1;
		while (cmd->args[++i])
		{
			if (!ft_strcmp(cmd->args[i], "$?"))
				cmd->args[i] = cut_line(cmd->args[i]);
			else if ((check_char(cmd->args[i], '$') > -1 \
				&& *cmd->args[i] != '\''))
			{
				while (check_char(cmd->args[i], '$') != -1)
				{
					pos = check_char(cmd->args[i], '$') + 1;
					tmp = check_variable(cmd, &i, &pos);
					cmd->args[i] = tmp;
				}
			}
		}
		cmd = cmd->next;
	}
}
