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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1 && (!s2 || !*s2))
		return ( NULL);
	else if (!s1)
		return (ft_strndup(s2, -1));
	else if (!s2)
		return (ft_strndup(s1, -1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = -1;
	new = malloc(sizeof(char) * (s1_len + s2_len + 1));
	while (s1[++i] != '\0')
		new[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		new[s1_len + i] = s2[i];
	new[s1_len + i] = '\0';
	return (new);
}

char	*append_with_nl(char *line, char *b)
{
	char	*tmp;
	char	*new;

	tmp = ft_strndup(b, ft_strnchr(b, '\n'));
	new = ft_strjoin(line, tmp);
	free(tmp);
	free(line);
	return (new);
}

void	reset_buffer(char *b)
{
	int		i;
	char	*tmp;
	
	if (!b)
		return ;
	i = -1;
	tmp = ft_strchr(b, '\n') + 1;
 	while (tmp[++i] != '\0')
		b[i] = tmp[i];
	b[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1];
	char		*line;
	int			num_read;
	
	line = NULL;
	// printf("b = %s\n", b);
	if (!ft_strchr(b, '\n'))
		line = ft_strjoin(line, b);
	else if (ft_strchr(b, '\n'))
	{
		line = append_with_nl(line, b);
		reset_buffer(b);
		// printf("%s", line);
		return (line);
	}
	while ((num_read = read(fd, b, BUFFER_SIZE)) && num_read > 0)
	{
		b[num_read] = '\0';
		if (ft_strchr(b, '\n'))
		{
			line = append_with_nl(line, b);
			reset_buffer((char *)b);
			break ;
		}
		else
			line = ft_strjoin(line, b);
	}
	// printf("%s", line);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*s;

	fd = open("file.txt", 0);
	/*
	get_next_line(fd);
	printf("------------\n");
	get_next_line(fd);
	printf("------------\n");
	get_next_line(fd);
	printf("------------\n");
	get_next_line(fd);
	printf("------------\n");
	get_next_line(fd);
	*/
	while ((s = get_next_line(fd)) && s != NULL)
	{
		printf("%s", s);
		free(s);
	}
}
