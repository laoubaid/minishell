/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 01:55:28 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/24 14:30:27 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char	*join_str(char *str1, char *str2);
int	join_expanded_key(char **str, char **current, t_param *param, int in);
char	*heredoc_expand(char *str, t_param *param)
{
	int i;
	int len;
	char	*exp;

	i = 0;
	exp = NULL;
	len = 0;
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

char	*ft_getstr(t_param *param, char *limiter, int fd, int exp)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	limiter = strjoin_optclean(limiter, "\n", 1);
	while (ft_strncmp(line, limiter, ft_strlen(line)) || (line && !line[0]))
	{
		if (line)
		{
			line = strjoin_optclean(line, "\n", 1);
			str = strjoin_optclean(str, line, 1);
		}
		free(line);
		line = readline("> ");
		if (!line)
		{
			write(1, "warning: here-doc delimited by end-of-file\n", 44);
			break ;
		}
	}
	char *freetmp = str;
	if (exp)
	{
		str = heredoc_expand(str, param);
		free(freetmp);
	}
	write(fd, str, ft_strlen(str));
	return (free(limiter), free(line), str);
}

char	*ft_heredoc(t_param *param, char *limiter, int num, int flag)
{
	char	*str;
	int		fd;
	char	*filename;

	filename = strjoin_optclean("/tmp/hdoc", ft_itoa(num), 2);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (NULL);
	str = ft_getstr(param, limiter, fd, flag);
	free(str);
	close(fd);
	return (filename);
}
