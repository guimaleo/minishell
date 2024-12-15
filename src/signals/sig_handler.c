#include "minishell.h"

void   ft_sighandler(int sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    // if (sig == SIGQUIT)
    
}

void    sig_handle()
{
    struct sigaction    sa;

    sa.sa_handler = ft_sighandler;
	sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sig");
        exit(1);
    }
    
}