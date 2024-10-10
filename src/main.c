#include "../include/minishell.h"

size_t  ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
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
    dup = (char *)malloc(n + 1);
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
    dup = (char *)malloc(ft_strlen(str) + 1);
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
        return (1);
    return (-1);
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
        i++;
    }
    vars->env[i] = NULL;
    i = 0;
    while (vars->env[i])
    {
        //printf("%s\n", vars->env[i]);
        ft_putstrfd(vars->env[i], 1);
        free(vars->env[i++]);
    }
    free(vars->env);
    free(vars);
}