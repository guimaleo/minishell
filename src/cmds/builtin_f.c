#include "minishell.h"

void    env_injection(t_cmd *cmd, char *tmp)
{
    int     i;
    char    **new_env;

    i = 0;
    while (cmd->env[i])
        i++;
    new_env = ft_calloc(i + 2, sizeof(*(cmd)->env));
    if (!new_env)
        return ;
    i = 0;
    while (cmd->env[i])
    {
        new_env[i] = ft_strdup(cmd->env[i]);
        i++;
    }
    new_env[i] = ft_strdup(tmp);
    free_doubles((void **)terminal()->env);
    terminal()->env = new_env;
}
void    export_f(t_cmd *cmd)
{
    int     i;
    size_t  len;
    char    *tmp;
    char    **to_exp;

    to_exp = ft_split(cmd->args[1], '=');
    if (!to_exp)
        return ;
    tmp = ft_strdup(cmd->args[1]);
    len = ft_strlen(to_exp[0]);
    i = 0;
    while (cmd->env[i])
    {
        if (!ft_strncmp(cmd->env[i], to_exp[0], len))
        {
            cmd->env[i] = tmp;
            return ;
        }
        i++;
    }
    env_injection(cmd, tmp);
    free(tmp);
    free_doubles((void **)to_exp);
}