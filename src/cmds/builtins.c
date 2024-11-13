#include "minishell.h"

int    check_builtin(t_cmd *cmd)
{
    int     i;
    int     j;
    char    *tmp[8] = BUILTIN;
    int     check;

    if (!cmd)
        return (-1);
    i = 0;
    check = 0;
    while (cmd->args[i])
    {
        j = 0;
        while(tmp[j])
        {
            if (!ft_strcmp(cmd->args[i], tmp[j]))
                check = exec_builtin(cmd);
            j++;
        }
        i++;
    }
    return (check);
}

void    echo_f(t_cmd *cmd)
{
    if (cmd->args[1] && !cmd->args[2])
        printf("%s", cmd->args[1]);
    if (ft_strncmp(cmd->args[1], "-n", 2) || !cmd->args[2])
        printf("\n");
    else if (cmd->args[2])
        printf("%s", cmd->args[2]);
}

int exec_builtin(t_cmd *cmd)
{
    builtin_func f;

    f = NULL;
    if (!ft_strcmp(cmd->args[0], "cd"))
        f = cd_f;
    else if (!ft_strcmp(cmd->args[0], "echo"))
        f = echo_f;
    else if (!ft_strcmp(cmd->args[0], "env"))
        f = env_f;
    else if (!ft_strcmp(cmd->args[0], "unset"))
        f = unset_f;
    else if (!ft_strcmp(cmd->args[0], "export"))
        f = export_f;
    else if (!ft_strcmp(cmd->args[0], "pwd"))
        f = pwd_f;
    else if (!ft_strcmp(cmd->args[0], "exit"))
        clean_exit(cmd, 1);
    else
        return (0);
    f(cmd);
    return (1);

}

void    replace_n_erase(t_cmd *cmd, char *input, size_t len)
{
    int     i;
    char    *swap;
    //char    *tmp;

    swap = NULL;
    i = 0;
    while (cmd->env[i] && ft_strncmp(cmd->env[i], input, len))
        i++;
    //tmp = cmd->env[i];
    printf("i do unset: %i\n", i);
    while (cmd->env[i])
    {
        swap = cmd->env[i + 1];
        if (swap == NULL)
        {
            cmd->env[i] = NULL;
            break ;
        }
        cmd->env[i] = swap;
        printf("swap: %s\n", swap);
        i++;
    }
    //free(tmp);
}

void   unset_f(t_cmd *cmd)
{
    int     i;
    bool    flag;
    size_t  len;
    char    *to_unset;

    flag = false;
    to_unset = ft_strdup(cmd->args[1]);
    if (!to_unset)
        return ;
    len = ft_strlen(to_unset);
    i = 0;
    while (cmd->env[i])
    {
        if (!ft_strncmp(cmd->env[i], to_unset, len))
            flag = true;
        i++;
    }
    if (flag)
        replace_n_erase(cmd, to_unset, len);
    
        // if (!ft_strncmp(cmd->env[i], to_unset, len))
        //     cmd->env[i] = NULL;

    // if (!ft_strcmp(to_unset, "PATH"))  SEGFAULT
    //     free(cmd->path);
    free(to_unset);
}
