#include "minishell.h"



t_cmd   *new_cmd(char **args)
{
    t_cmd   *init;

    init = ft_calloc(sizeof(t_cmd), 1);
    init->args = args;
    init->in = -1;
    init->out = -1;
    return (init);
}

