/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:29:24 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/17 23:30:15 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_children(int *all_stat)
{
	int		wstat;
	pid_t	pid;

	while (1)
	{
		pid = wait(&wstat);
		if (pid == -1)
		{
			if (errno == EINTR)
			{
				terminal()->stat = 128 + terminal()->sig;
				break ;
			}
			else
			{
				perror("wait");
				break ;
			}
		}
		if (WIFEXITED(wstat))
		{
			terminal()->stat = WEXITSTATUS(wstat);
			(void)all_stat;
			break ;
		}
	}
}
