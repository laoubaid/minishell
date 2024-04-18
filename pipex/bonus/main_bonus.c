/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:12:41 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/13 16:24:47 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	arg_error(int flag)
{
	if (flag == 1)
	{
		write(2, "Arguments not set correctly <cmd2+>!\n", 37);
		write(2, "Usage: [in_file] [cmd1] ... [cmdn] [out_file]...\n", 50);
		exit (2);
	}
	else if (flag == 2)
	{
		write(2, "Arguments not set correctly!\n", 29);
		write(2, "Usage: here_doc [limiter] [cmd1] [cmd2] [out_file]...\n", 54);
		exit (2);
	}
}

int	ft_multi_pipe(int ac, char **av, char **env)
{
	int		fd[2];
	int		ncmd;
	char	***args;

	ncmd = ac - 3;
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
	{
		write(2, av[1], ft_strlen(av[1]));
		perror(" ");
	}
	fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd[1] == -1)
	{
		write(2, av[ac - 1], ft_strlen(av[ac - 1]));
		perror(" ");
		exit(1);
	}
	args = get_args(ncmd, av, env);
	ft_pipex(fd, ncmd, args, env);
	return (0);
}

char	*ft_getstr(char *limiter)
{
	char	*line;
	char	*str;

	line = NULL;
	str = NULL;
	while (ft_strncmp(line, limiter, ft_strlen(line)) != 0)
	{
		str = ft_strjoin(str, line);
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	free(limiter);
	free(line);
	return (str);
}

int	ft_here_doc(int ac, char **av, char ***args, char **env)
{
	char	*str;
	int		f[2];
	int		**fd;

	fd = allocate_for_pipe(2);
	f[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (f[1] == -1)
		return (perror(""), 1);
	str = ft_getstr(ft_strjoin_and_keep(av[2], "\n"));
	pipe(fd[0]);
	pipe(fd[1]);
	write(fd[0][1], str, ft_strlen(str));
	free(str);
	if (fork() == 0)
		handle_cmd(fd[0], fd[1], args[0], env);
	else if (fork() == 0)
	{
		close(fd[0][1]);
		handle_cmd(fd[1], f, args[1], env);
	}
	ftclose(fd, 3, ft_free_cmd(args));
	fd_free(fd, ac - 4, 0);
	return (wait(NULL), wait(NULL), 0);
}

int	main(int ac, char **av, char **env)
{
	char	***args;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac != 6)
			arg_error(2);
		args = get_args(2, av + 1, env);
		ft_here_doc(ac, av, args, env);
		return (0);
	}
	if (ac < 5)
		arg_error(1);
	ft_multi_pipe(ac, av, env);
	return (0);
}
