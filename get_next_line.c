/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:19:42 by cabo-ram          #+#    #+#             */
/*   Updated: 2024/11/05 17:19:02 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > 4294967296 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*pile;
	char		buffer[BUFFER_SIZE];
	char		*line;

	line = join_pile(fd, pile, buffer);
	if (pile == NULL)
		return (NULL);
	return (line);
}

char	*ft_join_free(char *pile, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(pile, buffer);
	free (pile);
	return (temp);
}

char	*join_pile(int fd, char *pile, char *buffer)
{
	int		bytes;

	bytes = 1;
	pile = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (pile == NULL)
		return (ft_calloc(1, sizeof(char)));
	while (!ft_strchr(pile, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (fd < 0 || BUFFER_SIZE <= 0)
		{
			free (buffer);
			free (pile);
			return (NULL);
		}
		buffer[bytes] = '\0';
		pile = ft_join_free(pile, buffer);
	}
	free (buffer);
	return (get_subs(pile));
}

char	*get_subs(char *pile)
{
	size_t	i;
	char	*subs;
	size_t	j;
	char	*temp;

	i = 0;
	if (pile[i] == '\0')
		return (NULL);
	while (pile[i] && pile[i] == '\n')
		i++;
	subs = ft_substr(pile, 0, (i + 1));
	subs[++i] = '\0';
	j = i + 1;
	while (pile[j] != '\0')
		j++;
	temp = ft_substr(pile, i, j - i);
	free (pile);
	pile = ft_strdup(temp);
	return (subs);
}
