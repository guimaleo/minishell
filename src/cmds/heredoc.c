#include "minishell.h"

char **store_doc(char *input, char ** doc)
{
    int i;
    char **res;

    i = 0;
    while (doc[i])
        i++;
    res = (char **)malloc((i + 1) * sizeof(char*));
    if (!res)
        return (free_doubles(res), NULL);
    i = 0;
    while(doc[i])
    {
        res[i] = ft_strdup(doc[i]);
        if (!res)
            return(free_doubles(doc), free_doubles(res), NULL);
        i++;
    }
    free_doubles(doc);
    return (res);
}

int     here_doc(char *del)
{
    char *input;
    char **doc;
    doc = NULL;
    while (1)
    {
        input = readline("heredoc>");
        if (!ft_strcmp(input, del))
            break ;
        store_doc(input, doc);
    }
}