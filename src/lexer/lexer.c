/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:44:54 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 21:29:02 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cleanup_quotes(char *input)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	result = (char *)ft_calloc(ft_strlen(input) + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				result[j++] = input[i++];
			if (input[i] == quote)
				i++;
		}
		else
			result[j++] = input[i++];
	}
	return (result);
}

void	quote_analysis(t_cmd *cmd)
{
	int		i;
	char	*cleaned_arg;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			cleaned_arg = cleanup_quotes(cmd->args[i]);
			if (cleaned_arg)
			{
				free(cmd->args[i]);
				cmd->args[i] = cleaned_arg;
			}
			i++;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief This function will recognize any of the redirections tokens,
 * and inject the right escape sequence to it, to be splitted
 * @param str -> the new string with the injections
 * @param input -> the input from the prompt
 * @param i -> the position to be injected
 */
static int	redirections(char *str, char **input, size_t *i)
{
	if ((input[0][0] == '<' && input[0][1] == '<') || ((input[0][0] == '>' \
					&& input[0][1] == '>')))
	{
		str[(*i)++] = '\2';
		str[(*i)++] = (**input);
		str[(*i)++] = (**input);
		str[(*i)++] = '\2';
		(*input) += 2;
		return (1);
	}
	else if ((input[0][0] == '>') || (input[0][0] == '<'))
	{
		str[(*i)++] = '\2';
		str[(*i)++] = (**input);
		str[(*i)++] = '\2';
		(*input)++;
		return (1);
	}
	else if (input[0][0] == '|')
	{
		str[(*i)++] = '\3';
		(*input)++;
		return (1);
	}
	return (0);
}

/**
 *  @brief This function takes a flag to recognize if the string of input
 *  is in single or double quotes, and if it its, 
 *  it should not make any change in the quoted string
 * @param input -> fetched from readline
 * @param str -> the new string 3x bigger than the original input
 */
static char	*tokenization(char *str, char *input)
{
	char	flag;
	size_t	i;

	flag = 0;
	i = 0;
	if (!str)
		return (str);
	while (*input)
	{
		if (flag == 0 && (*input == '\"' || *input == '\''))
			flag = *input;
		else if (flag == *input)
			flag = 0;
		if (flag == 0 && *input == ' ')
			*input = '\2';
		if (!(flag == 0 && redirections(str, &input, &i)))
			str[i++] = *input++;
	}
	return (str);
}

/**
 * @brief Takes the input and allocates a string 3x bigger to inject
 * substitution values for the split of the tokens
 * @param input -> fetched from the readline
 */
void	lexer(char *input)
{
	char	*str;
	char	**pipes;
	size_t	i;
	t_cmd	*end;
	t_cmd	*tmp;

	str = tokenization(ft_calloc(ft_strlen(input), 3), input);
	pipes = ft_split(str, '\3');
	i = -1;
	while (pipes && pipes[++i])
	{
		tmp = new_cmd(ft_split(pipes[i], '\2'));
		check_redir(tmp);
		if (terminal()->cmd == NULL)
			terminal()->cmd = tmp;
		else
			end->next = tmp;
		end = tmp;
		free(tmp->path);
	}
	free_doubles((void **)pipes);
	free(str);
	exeggutor(terminal()->cmd);
	terminal()->cmd = NULL;
}
