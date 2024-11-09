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

int exec_builtin(t_cmd *cmd)
{
    builtin_func f;

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
    else
        return (0);
    f(cmd);
    return (1);

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

void    cd_f(t_cmd *cmd)
{
    //if !env do not work
    char    cwd[256];

    if (cmd->args[1])
    {
        if (ft_strcmp(cmd->args[1],"-"))
            {
                if (chdir(cmd->args[1]) == -1)
                    printf("%s%s\n", CD_ERR, cmd->args[1]);
                return; 
            }
        else
            chdir(getenv("OLDPWD"));
    }
    else
        chdir("/home");
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("cwd");
    else
       printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
void    env_f(t_cmd *cmd)
{
    int     i;

    if (!*(cmd)->env)
        return ;
    i = 0;
    while (cmd->env[i])
        printf("%s\n", cmd->env[i++]);
}

void   unset_f(t_cmd *cmd)
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
