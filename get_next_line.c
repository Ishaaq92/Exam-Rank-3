#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		s1_len;
	int		s2_len;
	int		i;

	if (!s1 && (!s2 || !*s2))
		return (NULL);
	else if (!s1 || !(*s1))
		return (ft_strndup(s2, -1));
	else if (!s2 || !(*s2))
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
	reset_buffer(b);
	return (new);
}

void	reset_buffer(char *b)
{
	int		i;
	char	*tmp;
	
	if (!b)
		return ;
	i = -1;
	tmp = ft_strchr(b, '\n');
	if (tmp == NULL)
	{
	    while (++i < BUFFER_SIZE)
	        b[i] = '\0';
	    return ;
	}
	tmp ++;
	 while (tmp[++i] != '\0')
		b[i] = tmp[i];
	b[i] = '\0';
	// printf("buffer = %s\n", b);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1];
	char		*line;
	int			num_read;
	
	if (fd < 0)
		return (NULL);
	line = NULL;
	if (!ft_strchr(b, '\n'))
	{
		line = ft_strjoin(line, b);
		reset_buffer(b);
	}
	else if (ft_strchr(b, '\n'))
	{
		line = append_with_nl(line, b);
		return (line);
	}
	while ((num_read = read(fd, b, BUFFER_SIZE)) && num_read > 0)
	{
		b[num_read] = '\0';
		if (!ft_strchr(b, '\n'))	
			line = ft_strjoin(line, b);
		else 
		{
			line = append_with_nl(line, b);
			break ;
		}
	}
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*s;
	int		i;

	fd = open("42_with_nl", 0);
	if (fd < 0)
		return (printf("invalid fd\n"), 1);
	i = 5;
	while ((s = get_next_line(fd)) && s != NULL && --i)
	{
		printf("%s", s);
		free(s);
	}
}
*/