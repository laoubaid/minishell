/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:55:28 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/17 17:09:16 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char *get_next_line(void)
{
	char *str;
	char *line;

	str = NULL;
	line = malloc(2);
	line[1] = 0;
	while (read(0, line, 1) > 0)
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
	int		flag;

	line = NULL;
	str = NULL;
	flag = 1;
	limiter = strjoin_optclean(limiter, "\n", 0);
	while (ft_strncmp(line, limiter, ft_strlen(line)))
	{
		str = strjoin_optclean(str, line, 1);
		free(line);
		write(1, "> ", 2);
		line = get_next_line();
		if (!line)
			break ;
	}
	free(limiter);
	free(line);
	write(fd, str, ft_strlen(str));
	return (str);
}

char	*ft_heredoc(char *limiter, int num)
{
	// need to give a unique name for each file
	char	*str;
	int		fd;
	char	*filename;

	filename = strjoin_optclean("/tmp/hdoc", ft_itoa(num), 2);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (NULL);
	str = ft_getstr(limiter, fd);
	free(str);
	close(fd);
	return (filename);
}
