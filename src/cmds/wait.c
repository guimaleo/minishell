#include "../inc/minishell.h"

void wait_children(int *all_stat)
{
    int wstat;
    pid_t pid;

    while (1)
    {
        pid = wait(&wstat);
        if (pid == -1)
        {
            if (errno == EINTR)
            {
                // If wait was interrupted by a signal, retry
                continue;
            }
            else
            {
                // Handle other errors
                perror("wait");
                break;
            }
        }

        if (WIFEXITED(wstat))
        {
            int exit_status = WEXITSTATUS(wstat);
            *all_stat = exit_status;
            printf("Process %d exited with status %d\n", pid, exit_status);
            break;
        }
    }
}