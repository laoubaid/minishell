/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:55:28 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/12 14:34:12 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char *get_next_line(int fd)
{
	char *str;
	char *line;

	if (fd < 0)
		return (NULL);
	str = NULL;
	line = malloc(2);
	line[1] = 0;
	while (read(fd, line, 1) > 0)
	{
		str = strjoin_optclean(str, line, 1);
		if (line[0] == '\n')
			return (free(line), str);
	}
	return (free(line), str);
}

char	*ft_getstr(char *limiter, int fd)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	limiter = strjoin_optclean(limiter, "\n", 0);
	while (ft_strncmp(line, limiter, ft_strlen(line)))
	{
		str = strjoin_optclean(str, line, 1);
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	free(limiter);
	free(line);
	write(fd, str, ft_strlen(str));
	return (str);
}

int	ft_heredoc(char *limiter)
{
	// need to give a unique name for each file
	char	*str;
	int		fd;

	fd = open(limiter, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (-1);
	str = ft_getstr(limiter, fd);
	free(str);
	close(fd);
	fd = open(limiter, O_RDONLY , 0664);
	return (fd);
}
