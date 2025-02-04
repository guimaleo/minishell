/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lede-gui <lede-gui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 22:33:56 by lede-gui          #+#    #+#             */
/*   Updated: 2025/02/04 22:35:28 by lede-gui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_line(char *str)
{
	char	*tmp;

	tmp = ft_itoa(terminal()->stat);
	free(str);
	return (tmp);
}
