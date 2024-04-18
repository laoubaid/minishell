/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:14:53 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/13 16:17:48 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	arg_error(void)
{
	write(2, "Arguments not set correctly!\n", 29);
	write(2, "Usage: [in_file] [cmd1] [cmd2] [out_file]...\n", 45);
	exit (2);
}

char	***get_args(int ncmd, char **av, char **env)
{
	char	***args;
	int		i;
	int		index;

	i = 0;
	index = getpath(env);
	args = malloc((ncmd + 1) * sizeof(char **));
	while (i < ncmd)
	{
		args[i] = ft_split(av[i + 2]);
		if (args[i][0] != NULL && is_path(args[i][0]) == 0 && index != -1)
			path(args + i, env[index]);
		i++;
	}
	args[i] = NULL;
	return (args);
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
		write(2, av[4], ft_strlen(av[4]));
		perror(" ");
		exit(1);
	}
	args = get_args(ncmd, av, env);
	ft_pipex(fd, ncmd, args, env);
	return (0);
}

int	main(int ac, char **av, char **ev)
{
	if (ac != 5)
		arg_error();
	ft_multi_pipe(ac, av, ev);
	return (0);
}
