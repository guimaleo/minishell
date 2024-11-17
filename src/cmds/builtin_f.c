#include "minishell.h"

void	pwd_f(t_cmd *cmd)
{
    char    *cwd;

    (void)cmd;
    cwd = getcwd(NULL, 0);
    if (cwd)
        printf("%s\n", cwd);
    free(cwd);
    return ;
}
void    cd_f(t_cmd *cmd)
{
    char    *tmp;

    if (cmd->args[1])
    {
        if (ft_strcmp(cmd->args[1],"-"))
        {
            if (chdir(cmd->args[1]) == -1)
                printf("%s%s\n", CD_ERR, terminal()->cwd);
            else
            {
                terminal()->old_cwd = terminal()->cwd;
                terminal()->cwd = getcwd(NULL, 0);
            }
        }
        else
        {
            tmp = terminal()->old_cwd;
            chdir(tmp);
            terminal()->old_cwd = terminal()->cwd;
            terminal()->cwd = tmp;
        }
    }
    else
    {
        chdir(terminal()->home);
        terminal()->cwd = getcwd(NULL, 0);
    }
    printf("%s\n", terminal()->cwd);
}

void    env_f(t_cmd *cmd)
{
    int     i;

    if (!*terminal()->env)
        return ;
    cmd->env = terminal()->env;
    i = 0;
    while (terminal()->env[i])
        printf("%s\n", terminal()->env[i++]);
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