/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:44:54 by lede-gui          #+#    #+#             */
/*   Updated: 2024/10/29 09:24:14 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		str[(*i)++] =  (**input);
		str[(*i)++] =  (**input);
		str[(*i)++] = '\2';
		(*input) += 2;
		return (1);
	}
	else if ((input[0][0] == '>') || (input[0][0] == '<'))
	{
		str[(*i)++] = '\2';
		str[(*i)++] =  (**input);
		str[(*i)++] = '\2';
		(*input)++;
		return (1);
	}
	else if (input[0][0] == '|')
	{
		str[(*i)++] =  '\3';
		(*input)++;
		return (1);
	}
	return (0);
}

/**
 *  @brief This function takes a flag to recognize if the string of input is in single
 * or double quotes, and if it its, it should not make any change in the quoted string
 * @param input -> fetched from readline
 * @param str -> the new string 3x bigger than the original input
 */
static char	*tokenization(char *str, char *input)
{
	char	flag;
	size_t	 i;

	flag = 0;
	i = 0;
	if (!str)
		return (str);
	while(*input)
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

	end = NULL;
	str = tokenization(ft_calloc(ft_strlen(input), 3), input);
	pipes = ft_split(str, '\3');
	/*prints importantes para visualização do lexer,
	substituir o \3 por 3 e \2 por 2 para facilitar a visualização*/
	// for (int j = 0; pipes[j]; j++)
	// {
	// 	// printf("cmd: %s\n", pipes[j]);
	// 	char **args = ft_split(str, '\3');
	// 	for (int k = 0; args[k]; k++)
	// 		printf("\tArgs: %s\n", args[k]);
	// 	free_doubles((void **)args);
	// }
	i = 0;
	while (pipes && pipes[i])
	{
		tmp = new_cmd(ft_split(pipes[i], '\2'));
		check_redir(tmp);
		// if (check_char(*tmp, '=')){
		// 	terminal()->expand = *tmp;
		// 	printf("Mandado para expansao: %s", *tmp);
		// 	printf("Salvo para expansao: %s", terminal()->expand);

		// }
		if (terminal()->cmd == NULL)
			terminal()->cmd = tmp;
		else
			end->next = tmp;
		end = tmp;
		i++;
	}
	free_doubles((void **) pipes);
	free(str);
	exeggutor(terminal()->cmd);
	terminal()->cmd = NULL;
}
