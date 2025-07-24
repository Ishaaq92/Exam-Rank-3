#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i ++;
	if (s[i] == c)
		return (&s[i]);
	return (NULL);
}

int	ft_strnchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i ++;
	if (s[i] == c)
		return (i + 1);
	return (-1);
}

char	*ft_strndup(char *s, int n)
{
	int		i;
	char	*new;

	i = -1;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[++i] != '\0' && (i < n || n == -1))
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}
