/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:48:40 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/19 19:55:03 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	ft_close_pipe(int *fd)
{
	printf("FECHA ESSA PORRRA\n");
	if (fd[0] && fd[0] > 2)
		close(fd[0]);
	if (fd[1] && fd[1] > 2)
		close(fd[1]);
}

void	ft_putcharfd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstrfd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		ft_putcharfd(str[i++], fd);
	ft_putcharfd(10, 1);
}
