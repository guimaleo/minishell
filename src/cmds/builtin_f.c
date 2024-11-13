#include "minishell.h"

void	pwd_f(t_cmd *cmd)
{
    char    *buffer;
    char    *cwd;

    (void)cmd;
    buffer = ft_calloc(2048, sizeof(char));
    if (!buffer)
        perror("getcwd error");
    cwd = getcwd(buffer, 2048);
    if (cwd)
    {
        printf("%s\n", cwd);
        free(buffer);
        return ;
    }
}
void    cd_f(t_cmd *cmd)
{
    //if !env do not work
    char    *buffer;

    terminal()->cwd = ft_calloc(1024, sizeof(terminal()->cwd));
    if (cmd->args[1])
    {
        if (ft_strcmp(cmd->args[1],"-"))
        {
            if (chdir(terminal()->cwd) == -1)
                printf("%s%s\n", CD_ERR, terminal()->cwd);
            return; 
        }
        else
            chdir(terminal()->old_cwd);
    }
    else
        chdir("/home");
    if (getcwd(terminal()->cwd, sizeof(terminal()->cwd)) == NULL)
        perror("cwd");
    else
       printf("%s\n", getcwd(terminal()->cwd, sizeof(terminal()->cwd)));
    //implement change old_cwd to cwd -> export both
    free(terminal()->cwd);
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