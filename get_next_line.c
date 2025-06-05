/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:30:39 by ishaaq            #+#    #+#             */
/*   Updated: 2025/06/05 16:08:42 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strnchr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i ++;
	if (s[i] == c)
		return (i);
	return (0);
}

char    *ft_strchr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i ++;
	if (s[i] == c)
		return (&s[i]);
	return (0);
}

int ft_strlen(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
		i ++;
	return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
	char    *new;
	int     i;
	int     s1_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	new = malloc(sizeof(char) * (s1_len + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		new[i] = s1[i];
	i = -1;
	while (s2[++i] != '\0')
		new[s1_len + i] = s2[i];
	new[s1_len + i] = '\0';
	return (new);
}

char    *ft_strndup(char *str, int bytes)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (bytes + 1));
	while (str[i] != '\0' && i < bytes)
	{
		new[i] = str[i];
		i ++;        
	}
	new[i] = '\0';
	return (new);
}

void	shift_bytes_line(char *line)
{
	char	*start;

	start = ft_strchr(line, '\n');
	free(line);
	if (ft_strchr(start, '\n') != 0)
		line = ft_strndup(start, ft_strnchr(start, '\n'));
	else
		line = ft_strchr(start, ft_strlen(start));
}

void	shift_bytes_buffer(char *line, char *buffer)
{
	char	*new;

	if (line)
		free(line);
	line = ft_strndup(ft_strchr(buffer, '\n') + 1, ft_strlen(ft_strchr(buffer, '\n')));
	// printf("remaining bytes = \'%s\'" , *line);
}

// Just appends the full BUFFER_SIZE number of characters and gets returned. 
char	*append_characters(char *line, char *buffer)
{
	char	*new;
	char	*tmp;

	// printf("not nl");
	if (!line)
	{
		line = ft_strndup(buffer, BUFFER_SIZE);
		return (line);
	}
	tmp = ft_strndup(buffer, BUFFER_SIZE);
	new = ft_strjoin(line, tmp);
	if (tmp)
		free(tmp);
	return (new);
}

// Getting returned
char	*append_characters_nl(char *line, char *buffer, int bytes)
{
	char	*temp;
	char	*new;

	if (!(line))
	{
		new = ft_strndup(buffer, ft_strnchr(buffer, '\n') + 1);
		shift_bytes_buffer(line, buffer);
		return (new);
	}
	temp = ft_strndup(buffer, ft_strnchr(buffer, '\n') + 1);
	new = ft_strjoin(line, temp);
	free(temp);
	shift_bytes_buffer(line, buffer);
	return (new);
}

char	*check_remaining_bytes_nl(char *line)
{
	int		i;
	char	*new;

	if (!line || ft_strchr(line, '\n') == NULL)
		return (NULL);
	new = ft_strndup(line, ft_strnchr(line, '\n') + 1);
	shift_bytes_line(line);
	return (new);
}

char	*halt(char *line)
{
	char	*new;
	
	if (!line || !(*line))
		return (NULL);
	new = ft_strndup(line, ft_strlen(line));
	// free(line);
	line[0] = '\0';
	return (new);
}

char    *get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	int			num_bytes;
	static char	*line;

	if (fd < 0)
		return (NULL);
	if (line && ft_strchr(line, '\n'))
		return (check_remaining_bytes_nl(line));
	while (42)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!num_bytes)
			return (halt(line));
		buffer[num_bytes] = '\0';
		if (ft_strchr(buffer, '\n'))
			return (append_characters_nl(line, buffer, ft_strnchr(buffer, '\n')));
		else
			line = append_characters(line, buffer);
	}
	return (line);
}

int main(int ac, char **av)
{
	int 	fd;
	char	*line;

	if (!access(av[1], O_RDONLY))
		fd = open(av[1], O_RDONLY);
	else
		fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	// printf("%s", line);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
}