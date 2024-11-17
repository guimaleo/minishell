#include "../inc/minishell.h"

void    check_acess(t_cmd *cmd)
{
    int i;
    char   *tmp;

    i = 0;
    if (!check_builtin(cmd))
    {
        if (!access(cmd->args[0], F_OK))
            execve(cmd->args[0], cmd->args, NULL);
        while (cmd->abs_build[i])
        {
            tmp = ft_strjoin_char(cmd->abs_build[i], cmd->args[0]);
            if (!access(tmp, F_OK))
                execve(tmp, cmd->args, terminal()->env);
            free(tmp);//free da lista
            i++;
        }
    }
    clean_exit(terminal()->cmd, 1);
    perror(cmd->args[0]);
}

void    child_process(t_cmd *cmd, int *fd, int *fd_in)
{
    dup2(*fd_in, STDIN_FILENO);
    if (cmd->next)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    check_acess(cmd);
    exit(1);
}

void    parent_process(int *fd, int *fd_in)
{
    wait(NULL);
    close(fd[1]);
    if (*fd_in != 0)
    close(*fd_in);
    *fd_in = fd[0];
}

void    pipex(t_cmd *cmd)
{
    int fd[2];
    pid_t   pid;
    int     fd_in = 0;

    while(cmd)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
            child_process(cmd, fd, &fd_in);
        else
        {
            parent_process(fd, &fd_in);
            cmd = cmd->next;
        }
    }
    if (fd_in != 0)
        close(fd_in);
}
