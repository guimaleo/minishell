/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:44:54 by lede-gui          #+#    #+#             */
/*   Updated: 2024/10/25 23:27:55 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int    redirections(char *str, char **input, size_t *i)
{
    if ((input[0][0] == '<' && input[0][1] == '<') || ((input[0][0] == '>' \
    && input[0][1] == '>')))
    {
        str[(*i)++] = '2';
        str[(*i)++] =  (**input);
        str[(*i)++] =  (**input);
        str[(*i)++] = '2'; 
        (*input) += 2;
        return (1);
    }
    else if ((input[0][0] == '>') || (input[0][0] == '<'))
    {
        str[(*i)++] = '2';
        str[(*i)++] =  (**input);
        str[(*i)++] = '2'; 
        (*input)++;
        return (1);
    }
    else if (input[0][0] == '|')
    {
        str[(*i)++] =  '3';
        (*input)++;
        return (1);
    }
    return (0);
}

static void    tokenization(char *str, char *input)
{
    char    flag;
    size_t     i;

    flag = 0;
    i = 0;
    while(*input)
    {
        if (flag == 0 && (*input == '\"' || *input == '\''))
            flag = *input;
        else if (flag == *input)
            flag = 0;
        if (flag == 0 && *input == ' ')
            *input = '2';
        if (!(flag == 0 && redirections(str, &input, &i)))
            str[i++] = *input++;
    }
}

void    lexer(char *input)
{
    char    *str;

    str = ft_calloc(ft_strlen(input), 3);
    if (!str)
        return ;
    tokenization(str, input);
    printf("str: %s\n", str);
    free(str);
}