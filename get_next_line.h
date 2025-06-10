/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:36:25 by ishaaq            #+#    #+#             */
/*   Updated: 2025/06/06 17:50:36 by ishaaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

#define BUFFER_SIZE 3 

int	    ft_strnchr(char *s, char c);
char    *ft_strchr(char *s, char c);
int     ft_strlen(char *str);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_strndup(char *str, int bytes);

// public
char    *get_next_line(int fd);


#endif
