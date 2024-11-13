#include "../inc/minishell.h"

bool    check_forced()
{

}
/**
 * @brief Checks if the variable was set either by an export command, and thus
 * sent to the environment, or it was set in the command line
 * @param   t_cmd *cmd 
 */
bool		check_variable(t_cmd *cmd)
{
    size_t  len;
    int     i;
    char    **split;
    char    *tmp;

    i = 0;
    while (terminal()->split_input[i])
    {
        if (!ft_strncmp(terminal()->split_input[i], "$", 1));
            terminal()->expand = terminal()->split_input[i];
        i++;
    }
    i = 0;
    tmp = ft_strdup(cmd->args[0] + 1);
    while (cmd->env[i])
    {
        if (!ft_strncmp(tmp, cmd->env[i], len))
        {
            split = ft_split(tmp, '=');
            printf("%s", split[1]);
            return (true);
        }
        i++;
    }
    if (check_forced())
        return (true);
    return (false);
}