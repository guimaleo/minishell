#include "../inc/minishell.h"

size_t  ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str) // if(!str ||!*str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char    *ft_strndup(char *str, int  n)
{
    int i;
    int len;
    char *dup;

    i = 0;
    if (!str)
        return (NULL);
    len = ft_strlen(str) + 1;
    if (len > n)
        len = n;
    dup = (char *)calloc(1, n + 1);
    if (!dup)
        return (NULL);
    while (str[i] && i < len)
    {
        dup[i] = str[i];
        i++;
    }
    return (dup);
}



char    *ft_strdup(char *str)
{
    int i;
    char *dup;

    i = 0;
    if (!str)
        return (NULL);
    dup = (char *)calloc(1, ft_strlen(str) + 1);
    if (!dup)
        return (NULL);
    while (str[i])
    {
        dup[i] = str[i];
        i++;
    }
    return (dup);
}

int ft_strncmp(char *s1, char *s2, int n)
{
    int i;

    i = 0;
    while (s1[i] == s2[i] && i < n)
        i++;
    if (i == n)
        return (0);
    return (1);
}

void    ft_putcharfd(char c, int fd)
{
    write(fd, &c, 1);
}

void    ft_putstrfd(char *str, int fd)
{
    int i;

    i = 0;
    if (!str)
        return;
    while(str[i])
        ft_putcharfd(str[i++], fd);
    ft_putcharfd(10, 1);
}

int ft_countwords(char *str, char c)
{
    int count;
    int i;

    count = (str[0] != c);
    i = 0;
    i++;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

char    **ft_split(char *str, char c)
{
    int i;
    int j;
    int end;
    char **split;

    i = 0;
    j = 0;
    if (!str || !str[0])
        return (NULL);
    split = (char **)calloc(1, (ft_countwords(str, c) + 1 ) * sizeof(char *));
    while (str[i])
    {
        while (str[i] == c)
            i++;
        end = 0;
        while (str[end + i] && str[end + i] != c)
            end++;
        split[j] = ft_strndup(str + i, end);
        j++;
        i += end;
        i++;
    }
    split[j] = NULL;
    return (split);
}

int main(int ac, char *av[], char **env)
{
    int i;
    t_env *vars;

    if (!env)
        exit(1);
    vars = (t_env *)calloc(1, sizeof(t_env));
    if (!vars)
        return (1);
    i = 0;
    while (env[i])
        i++;
    vars->env = (char **)calloc(1, (i + 1) * sizeof(char *));
    if (!vars->env)
        exit(1);
    i = 0;
    while (env[i])
    {
        vars->env[i] = ft_strdup(env[i]);
        // if (!vars->env[i])
        // {
        //     while (i)
        //         free(vars->env[i--]);
        // }
        if (!ft_strncmp(vars->env[i], "PATH=", 5))
            vars->paths = ft_split(vars->env[i], ':');
        i++;
    }
    vars->env[i] = NULL;
    i = 0;
    while (vars->env[i])
    {
        //printf("%s\n", vars->env[i]);
        //ft_putstrfd(vars->env[i], 1);
        free(vars->env[i++]);
    }
    i = 0;
    while (vars->paths[i])
    {
        //printf("%s\n", vars->env[i]);
        ft_putstrfd(vars->paths[i], 1);
        free(vars->paths[i++]);
    }
    free(vars->paths);
    free(vars->env);
    free(vars);
}