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
            terminal()->stat = WEXITSTATUS(wstat);
            (void)all_stat;
            printf("Process %d exited with status %d\n", pid, terminal()->stat);
            break;
        }
    }
}