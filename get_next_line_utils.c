/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaaq <ishaaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 06:07:06 by ishaaq            #+#    #+#             */
/*   Updated: 2025/06/06 18:35:29 by ishaaq           ###   ########.fr       */
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
    if (s1_len == 0)
        return (ft_strndup(s2, ft_strlen(s2)));
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
