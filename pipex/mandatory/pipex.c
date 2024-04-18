/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 19:19:01 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/13 14:06:26 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_cmd(int *fdin, int *fdout, char **cmd, char **ev)
{
	close(fdin[1]);
	close(fdout[0]);
	dup2(fdin[0], STDIN_FILENO);
	dup2(fdout[1], STDOUT_FILENO);
	close(fdin[0]);
	close(fdout[1]);
	if (fdin[0] == -1)
		return (127);
	if (cmd[0] != NULL)
	{
		execve(cmd[0], cmd, ev);
		if (cmd[0][0] == '/' || cmd[0][0] == '.')
			return (perror(""), 127);
	}
	write(2, "command not found: ", 19);
	if (cmd[0])
		write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "\n", 1);
	return (127);
}

int	**allocate_for_pipe(int n)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * n);
	while (i < n)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	return (fd);
}

int	ftclose(int **fd, int n, int flag)
{
	if (flag)
	{
		close(fd[n - 1][1]);
		close(fd[n][0]);
	}
	while (n - 2 >= 0)
	{
		close(fd[n - 2][0]);
		close(fd[n - 2][1]);
		n--;
	}
	return (1);
}

void	ftwait(int **fd, int ncmd)
{
	fd_free(fd, ncmd, 0);
	while (wait(NULL) != -1)
	{
	}
}

int	ft_pipex(int files[2], int ncmd, char ***cmd, char **ev)
{
	int	**fd;
	int	i;

	i = 0;
	fd = allocate_for_pipe(ncmd);
	while (i <= ncmd - 1)
	{
		if (i != ncmd - 1)
			pipe(fd[i]);
		if (fork() == 0)
		{
			if (i == 0)
				handle_cmd(files, fd[0], cmd[i], ev);
			else if (i == ncmd - 1)
				handle_cmd(fd[i - 1], files, cmd[i], ev);
			else
				handle_cmd(fd[i - 1], fd[i], cmd[i], ev);
			return (fd_free(fd, ncmd, ft_free_cmd(cmd)), 127);
		}
		if (i != ncmd - 1)
			close(fd[i][1]);
		i++;
	}
	ftclose(fd, ncmd, ft_free_cmd(cmd));
	return (ftwait(fd, ncmd), 0);
}
