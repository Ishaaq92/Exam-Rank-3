/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:30:39 by ishaaq            #+#    #+#             */
/*   Updated: 2025/06/09 21:07:43 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


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
	if (line)
		free(line);
	line = ft_strndup(ft_strchr(buffer, '\n') + 1, ft_strlen(ft_strchr(buffer, '\n') + 1));
}

// Just appends the full num_bytes number of characters and gets returned. 
char	*append_characters(char *line, char *buffer, int num_bytes)
{
	char	*new;
	char	*tmp;

	printf("not nl");
	if (!line)
	{
		line = ft_strndup(buffer, num_bytes);
		// printf("debugging = %s", new);
		return (line);
	}
	tmp = ft_strndup(buffer, num_bytes);
	printf("tmp = %s", tmp);
	new = ft_strjoin(line, tmp);
	if (tmp)
		free(tmp);
	printf("debugging = %s\n", new);
	return (new);
}

// Getting returned
char	*append_characters_nl(char *line, char *buffer, int bytes)
{
	char	*temp;
	char	*new;

	if (!(line))
	{
		new = ft_strndup(buffer, bytes + 1);
		shift_bytes_buffer(line, buffer);
		return (new);
	}
	temp = ft_strndup(buffer, bytes + 1);
	new = ft_strjoin(line, temp);
	if (temp)
		free(temp);
	shift_bytes_buffer(line, buffer);
	return (new);
}

char	*check_remaining_bytes_nl(char *line)
{
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
	printf("here\n");
	while (42)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (!num_bytes)
			return (halt(line));
		buffer[num_bytes] = '\0';
		printf("%d, %s\n", num_bytes, buffer);
		if (ft_strchr(buffer, '\n'))
			return (append_characters_nl(line, buffer, ft_strnchr(buffer, '\n')));
		else
			line = append_characters(line, buffer, num_bytes);
	}
	return (line);
}

int main(int ac, char **av)
{
	int 	fd;
	char	*line;

	(void) ac;	
	if (!access(av[1], O_RDONLY))
		fd = open(av[1], O_RDONLY);
	else
		fd = open("file.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// line = get_next_line(fd);
	// while (line != NULL)
	// {
	// 	printf("%s", line);
	// 	line = get_next_line(fd);
	// }
}