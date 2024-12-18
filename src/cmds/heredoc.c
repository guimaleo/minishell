#include "minishell.h"

void here_doc(t_cmd *cmd, char *del, char *str)
{
    char *input;
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid == 0)
    {
        if (!str)
        {
            close(fd[1]);
            fd[1] = 1;
        }
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        while (1)
        {
            input = readline("heredoc> ");
            if (!input || !ft_strcmp(input, del))
            {
                free(input);
                break;
            }
            write(fd[1], input, ft_strlen(input));
            write(fd[1], "\n", 1);
            free(input);
        }
        close(fd[1]);
        cmd->in = fd[0];
        exit(0);
    }
    else
    {
        close(fd[1]);
        waitpid(pid, NULL ,0);
        printf("HERE\n");
        cmd->in = fd[0];
    }
}

void check_here(t_cmd *cmd)
{
    int i = 0;
    while (cmd->args[i])
    {
        if (!ft_strncmp(cmd->args[i], "<<", 2))
        {
            here_doc(cmd, cmd->args[i + 1], cmd->args[i + 2]);
            free(cmd->args[i]);
            free(cmd->args[i + 1]);
            cmd->args[i] = NULL;
            break;
        }
        i++;
    }
}