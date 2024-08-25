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
#include "parser.h"

char	*heredoc_expand(char *str, t_param *param)
{
	int		len;
	char	*exp;

	len = 0;
	exp = NULL;
	while (str[len])
	{
		if (str[len] == '$')
		{
			if (len)
				exp = join_str(exp, ft_substr(str, 0, len));
			str += len +1;
			if ((len && !(exp))
				|| join_expanded_key(&str, &exp, param, 0))
				return (NULL);
			len = 0;
		}
		else
			len++;
	}
	if (len)
		exp = join_str(exp, ft_substr(str, 0, len));
	return (exp);
}

char	*ft_getstr(char *limiter)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	limiter = join_optclean(limiter, "\n", 1);
	while (ft_strncmp(line, limiter, ft_strlen(line)) || (line && !line[0]))
	{
		if (line)
		{
			line = join_optclean(line, "\n", 1);
			str = join_optclean(str, line, 1);
		}
		free(line);
		line = readline("> ");
		if (line && !line[0] && limiter[0] == '\n')
			break ;
		if (!line)
		{
			write(1, "warning: here-doc delimited by end-of-file\n", 44);
			break ;
		}
	}
	return (free(limiter), free(line), str);
}

char	*ft_heredoc(t_param *param, char *limiter, int num, int exp)
{
	char	*str;
	char	*tmp;
	int		fd;
	char	*filename;

	filename = join_optclean("/tmp/hdoc", ft_itoa(num), 2);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (NULL);
	str = ft_getstr(limiter);
	tmp = str;
	if (exp && str && str[0])
	{
		str = heredoc_expand(str, param);
		free(tmp);
	}
	write(fd, str, ft_strlen(str));
	free(str);
	close(fd);
	return (filename);
}
