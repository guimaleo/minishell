#include "minishell.h"

void    check_builtin(t_cmd *cmd)
{
    int     i;
    int     j;
    char    *tmp[8] = BUILTIN;

    i = 0;
    while (cmd->args[i])
    {
        j = 0;
        while(tmp[j])
        {
            if (!ft_strcmp(cmd->args[i], tmp[j]))
                exec_builtin(cmd);
            j++;
        }
        i++;
    }
}

void    exec_builtin(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->args[0], "cd"))
        cd_builtin(cmd);
    if (!ft_strcmp(cmd->args[0], "echo"))
        echo_builtin(cmd);
    if (!ft_strcmp(cmd->args[0], "env"))
        env_builtin(cmd);
    if (!ft_strcmp(cmd->args[0], "unset"))
        unset_builtin(cmd);
}

void    echo_builtin(t_cmd *cmd)
{
    if (cmd->args[1])
        printf("%s", cmd->args[1]);
    if (ft_strcmp(cmd->args[0], "-n") || !cmd->args[1])
        printf("\n");
}

void    cd_builtin(t_cmd *cmd)
{
    //if !env do not work
    if (cmd->args[1])
    {
        if (ft_strcmp(cmd->args[1],"-"))
            chdir(cmd->args[1]);
        else
            chdir(getenv("OLDPWD"));
    }
    else
        chdir("/home");
}
void    env_builtin(t_cmd *cmd)
{
    int     i;

    if (!*(cmd)->env)
        return ;
    i = 0;
    while (cmd->env[i])
        printf("%s\n", cmd->env[i++]);
}

void   unset_builtin(t_cmd *cmd)
{
    int     i;
    size_t  len;
    char    *to_unset;

    to_unset = ft_strdup(cmd->args[1]);
    if (!to_unset)
        return ;
    len = ft_strlen(to_unset);
    i = 0;
    while (cmd->env[i])
    {
        if (!ft_strncmp(cmd->env[i], to_unset, len))
            cmd->env[i] = NULL;
        i++;
    }
    // if (!ft_strcmp(to_unset, "PATH"))  SEGFAULT
    //     free(cmd->path);
    free(to_unset);
}