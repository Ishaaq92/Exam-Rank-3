#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		ft_strlen(char *s);
char	*ft_strchr(char *s, char c);
int		ft_strnchr(char *s, char c);
char	*ft_strndup(char *s, int n);
void	reset_buffer(char *b);

#endif
