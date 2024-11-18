#include "../inc/minishell.h"

static int	ft_isspace(char c)
{
	return ((c > 8 && c < 14) || c == 32);
}

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

int		ft_atoi(char *s)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;

	while (ft_isspace(*s))
		s++;
	if (*s == 43 || *s == 45)
	{
		if (*s == 45)
			sign = -1;
		s++;
	}
	while (*s > 47 && *s < 58)
		res = res * 10 + ((*s++ - 48) * sign);
	return(res);
}
