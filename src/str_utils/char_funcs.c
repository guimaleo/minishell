#include "../inc/minishell.h"

int	check_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_substr(char * s, int start, int size)
{
	int i;
	char *sub;

	sub = (char *)ft_calloc(size + 1, sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < size)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	return (sub);
}