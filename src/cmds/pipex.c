#include "../inc/minishell.h"

void    check_acess(t_cmd *cmd)
{
    int i;
    char   *tmp;

    i = 0;
    if (!access(cmd->args[0], F_OK))
        execve(cmd->args[0], cmd->args, NULL);
    while (cmd->abs_build[i])
    {
        tmp = ft_strjoin_char(cmd->abs_build[i], cmd->args[0]);
        if (!access(tmp, F_OK))
            execve(tmp, cmd->args, NULL);
        free(tmp);
        i++;
    }
    perror(cmd->args[0]);
}



void    pipex(t_cmd *cmd)
{
    int fd[2];
    pid_t   pid;
    //char    *tmp;
    int     fd_in = 0;
    //int i;

    //i = 0;
    while(cmd)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            dup2(fd_in, STDIN_FILENO);
            if (cmd->next)
                dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            check_acess(cmd);
            exit(1);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            if (fd_in != 0)
                close(fd_in);
            fd_in = fd[0];
            cmd = cmd->next;
        }
    }
    if (fd_in != 0)
        close(fd_in);
}
