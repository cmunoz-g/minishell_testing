#include "minishell.h"

int		check_spaces(char *line)
{
	size_t	i;
	size_t	len;
	
	i = 0;
	len = ft_strlen(line);
	while (i < len && (line[i] == ' ' || line[i] == '	' || line[i] == '\n'))
		i++;
	if (i == len)
		return (1);
	else
		return (0);
}

char	*ft_strdup_mod(const char *s, size_t size)
{
	char	*cpy;

	cpy = (char *)malloc(size);
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, s, size + 1);
	return (cpy);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\f' || c == '\v' || c == '\r' || c == ' ')
		return (1);
	return (0);
}