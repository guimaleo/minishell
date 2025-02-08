/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:39 by lede-gui          #+#    #+#             */
/*   Updated: 2024/12/17 23:23:25 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_cmd **list)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = *list;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	*list = NULL;
}

/**
 * @brief frees any double pointer variable if it is typecasted as a void **
 * @param void	**ptr
 */
void	free_doubles(void **ptr)
{
	size_t	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}
/**
 * @brief allocates the number of bytes len in a pointer of size size
 * setting the full block to \0 (NUL)
 * @param len
 * @param size
 */

void	*ft_calloc(size_t len, size_t size)
{
	size_t			i;
	void			*ptr;
	unsigned char	*byte;

	if (!len || !size)
		return (NULL);
	i = 0;
	byte = NULL;
	ptr = malloc(len * size);
	if (!ptr)
		return (NULL);
	byte = (unsigned char *)ptr;
	while (i < (len * size))
		byte[i++] = 0;
	return (ptr);
}

void	ft_copyenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	terminal()->env = (char **)ft_calloc((i + 1) * sizeof(char *), 1);
	if (!terminal()->env)
		exit(1);
	i = 0;
	while (env[i])
	{
		terminal()->env[i] = ft_strdup(env[i]);
		if (!terminal()->env[i])
			free_doubles((void **)terminal()->env);
		i++;
	}
	terminal()->env[i] = NULL;
	return ;
}
