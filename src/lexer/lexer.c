/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:44:54 by lede-gui          #+#    #+#             */
/*   Updated: 2024/11/25 17:44:32 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// $HOME "Aqui expande $HOME" 'Aqui nao expande $MAKELEVEL' "aqui expande '$worked?'" "na proxima tambem expande" $PATH

void	quote_analysis(t_cmd *cmd)
{
	int		i;
	int		j;
	int		to_rm;
	char	*tmp;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '\'' || cmd->args[i][0] == '\"')
		{
			j = 1;
			to_rm = cmd->args[i][0];
			while (cmd->args[i][j] && cmd->args[i][j] != to_rm)
				j++;
			if (!cmd->args[i][j])
				printf("Syntax error: unquoted string\n");//TODO: ignorar qualquer argumento que venha após um syntax error
			tmp = ft_substr(cmd->args[i], 1, (j - 1));
			terminal()->cmd->args[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
}

char	*inject_expansion(char *input, char *key, char *value)
{
	size_t	len;
	char	*expanded;
	char	*treated;
	size_t		i;
	size_t		j;
	size_t		r;

	len = ft_strlen(input) + ft_strlen(value);
	expanded = ft_calloc(len + 1, 1);
	i = check_char(input, '$') + 1;
	// printf("%lu\n", i);
	j = 0;
	// printf("Input Passo 0: %s\n", input);
	while (j < i && *input != '$')
		expanded[j++] = *(input)++;
	input++;
	// printf("Passo 1: %s\n", expanded);
	// printf("Input Passo 1: %s\tChar %c %i\n", input, *input, *input);
	// printf("Key: %s\n", key);
	while (*key)
	{
		// printf("Key exclusion: %c %c\n", *key, *input);
		input++;
		key++;
	}
	// printf("Input Passo 2: %s\t Char: %i\n", input, *input);
	r = 0;
	while (value[r])
		expanded[j++] = value[r++];
	// printf("Passo 2: %s\n", expanded);
	// printf("Input Passo 3: %s\tchar: %i\n", input, *input);
	while (j < len && *input)
		expanded[j++] = *(input)++;
	// printf("Passo 3: %s\n", expanded);
	// printf("Input Passo 4: %s\n", input);
	// input = NULL;
	// printf("Passo 4: %s\n", expanded);
	// printf("Input Passo 5: %s\n", input);
	treated = ft_strdup(expanded);
	free(expanded);
	// printf("Input Passo 6: %s\n", input);
	// printf("input expandido: %s\n", treated);
	return (treated);
	// free(expanded);
}

char	*check_variable(t_cmd *cmd, int *i, int *pos)
{
	char	*str[3];
	char	**tmp;
	int		it[3];

	it[0] = *pos;
	// printf("%i\n", it[0]);
	// while (cmd->args[*i][*pos] && ft_isupper(cmd->args[*i][*pos]))
	// 	(*pos)++;
	while ((cmd->args[*i][*pos] && !ft_isspace(cmd->args[*i][*pos]) && \
	(cmd->args[*i][*pos] != '\"' && cmd->args[*i][*pos] != '\'')))
		(*pos)++;
	// printf("pos: %i", *pos);
	it[1] = *pos - it[0];
	str[0] = ft_substr(cmd->args[*i], it[0], it[1]);
	it[2] = 0;
	while (cmd->args[*i][it[0]] && (cmd->args[*i][it[0]] != '\'' && cmd->args[*i][it[0]] != '\"'))
		str[0][it[2]++] = cmd->args[*i][it[0]++];
	it[0] = 0;
	while (terminal()->env[it[0]])
	{
		if (!ft_strncmp(terminal()->env[it[0]], str[0], it[1]))
		{
			tmp = ft_split(terminal()->env[it[0]], '=');
			str[1] = ft_strdup(tmp[1]);
			free_doubles((void **)tmp);
			// printf("Key: %s\nPara expandir: %s\n", str[0], str[1]);
			str[2] = inject_expansion(cmd->args[*i], str[0], str[1]);
			free(str[0]);
			free(str[1]);
			free(cmd->args[*i]);
			return (str[2]);
		}
		it[0]++;
	}
	return (0);
}

void	expansions(t_cmd *cmd)
{
	int		i;
	int		pos;

	i = 0;
	while (cmd->args[i])
	{
		pos = check_char(cmd->args[i], '$');
		if (check_char(cmd->args[i], '$') > -1 && *cmd->args[i] != '\'')
		{
			// printf("char na pos[0] das strings passadas para checar: %c\n", cmd->args[i][0]);
			// printf("Char encontrado: %c\n", cmd->args[i][pos]);
			pos++;
			terminal()->cmd->args[i] = check_variable(cmd, &i, &pos);
		}
		// printf("Args sendo verificados para expansion: %s\n", cmd->args[i]);
		i++;
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
	// 	 for (int k = 0; args[k]; k++)
	// 	 	printf("\tArgs: %s\n", args[k]);
	// 	free_doubles((void **)args);
	// }
	i = 0;
	while (pipes && pipes[i])
	{

		tmp = new_cmd(ft_split(pipes[i], '\2'));
		//for (int k = 0; tmp->args[k]; k++)
		 	//printf("\tArgs: %s\n", tmp->args[k]);
		check_redir(tmp);
		check_redout(tmp);

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
	free_doubles((void **)pipes);
	free(str);
	expansions(terminal()->cmd);
	// char **tst1 = (char **)terminal()->cmd->args;
	// for(int x = 0; tst1[x]; x++)
		// printf("testing: %s\n", tst1[x]);
	quote_analysis(terminal()->cmd);
	// char **tst = (char **)terminal()->cmd->args;
	// for(int x = 0; tst[x]; x++)
	// 	printf("testing: %s\n", tst[x]);
	exeggutor(terminal()->cmd);
	terminal()->cmd = NULL;
}
