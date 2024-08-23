/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:55:28 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/23 23:54:24 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char *get_next_line(void)
{
	char	*str;
	char	*line;

	str = NULL;
	line = malloc(2);
	line[1] = 0;
	while (read(0, line, 1) > 0)
	{
		str = strjoin_optclean(str, line, 1);
		if (line[0] == '\n')
			return (free(line), str);
	}
	write(1, "\n", 1);
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
	limiter = strjoin_optclean(limiter, "\n", 1);
	while (ft_strncmp(line, limiter, ft_strlen(line)))
	{
		str = strjoin_optclean(str, line, 1);
		free(line);
		write(1, "> ", 2);
		line = get_next_line();
		if (!line)
		{
			write(1, "warning: here-doc delimited by end-of-file\n", 44);
			break ;
		}
	}
	write(fd, str, ft_strlen(str));
	return (free(limiter), free(line), str);
}

char	*ft_heredoc(char *limiter, int num)
{
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
