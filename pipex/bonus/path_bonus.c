/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:45:58 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/13 16:22:22 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	is_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	getpath(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (!(ft_strncmp(ev[i], "PATH=", 5)))
			return (i);
		i++;
	}
	return (-1);
}

int	path(char ***p, char *ev)
{
	char	**paths;
	char	*cmd;
	int		i;

	i = 0;
	paths = ft_split_path(&ev[5], ':');
	while (paths[i])
	{
		cmd = ft_strjoin_and_keep(paths[i], (*p)[0]);
		if (access(cmd, X_OK) == 0)
		{
			free((*p)[0]);
			(*p)[0] = cmd;
			ft_free(paths);
			return (0);
		}
		free(cmd);
		i++;
	}
	ft_free(paths);
	return (1);
}
