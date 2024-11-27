#include "../inc/minishell.h"

void wait_children(int *all_stat, int *proc)
{
    int wstat;
    int count;
    pid_t pid;

    count = 0;
    while (count < *proc)
    {
        pid = wait(&wstat);
        printf("%d\n", pid);
        if(WIFEXITED(wstat))
        {
            terminal()->stat = WEXITSTATUS(wstat);
            all_stat[count++] = terminal()->stat;
        }
    }
}