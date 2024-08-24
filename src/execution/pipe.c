/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:28:54 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/24 14:45:03 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	pipe_init(t_param *param, t_ast *ast, t_pipe *pip)
{
	param->ast = ast;
	expander(param);
	pip->param = param;
	pip->node = NULL;
	if (ast->type == LPAREN)
		pip->node = ast;
	pip->cmd = ast->cmd;
	pip->next = NULL;
}

int	**ft_pipe_allocatexfree(t_pipe *pip, int *n, int flag)
{
	int		i;
	int		**fd;
	t_pipe	*tmp;

	i = 0;
	tmp = NULL;
	if (flag)
	{
		while (pip->next)
		{
			tmp = pip->next;
			free(pip);
			pip = tmp;
		}
		free(pip);
		return (NULL);
	}
	*n = 0;
	while (pip && ++*(n))
		pip = pip->next;
	fd = malloc(sizeof(int *) * (*n));
	while (i < *n)
		fd[i++] = malloc(2 * sizeof(int));
	return (fd);
}

void	handle_cmd(t_pipe *pip, int *fdin, int *fdout, char **env)
{
	int		exit_status;

	if (fdin)
	{
		close(fdin[1]);
		dup2(fdin[0], STDIN_FILENO);
		close(fdin[0]);
	}
	if (fdout)
	{
		close(fdout[0]);
		dup2(fdout[1], STDOUT_FILENO);
		close(fdout[1]);
	}
	if (pip->node)
	{
		pip->param->ast = pip->node;
		exit(subshell(pip->param));
	}
	if (!pip->cmd->simple_cmd[0])
		exit(openfiles(pip->param));
	exit_status = builtins(pip->param, pip->cmd);
	if (exit_status != -1)
		exit (exit_status);
	cmd_execve(pip->cmd->simple_cmd, env, pip->cmd->redirs);
}

int	closexwait(int **fd, int count, int pid)
{
	int	i;
	int	exit_status;

	i = count;
	exit_status = 0;
	while (count - 2 >= 0)
	{
		close(fd[count - 2][0]);
		close(fd[count - 2][1]);
		count--;
	}
	count = i;
	i = 0;
	while (i < count)
		free(fd[i++]);
	free(fd);
	waitpid(pid, &exit_status, 0);
	while (wait(NULL) != -1)
	{
	}
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	return (1);
}

int	handle_pipe(t_pipe *pip, char **env, int i)
{
	int	**fd;
	int	count;
	int	pid;

	fd = ft_pipe_allocatexfree(pip, &count, 0);
	while (++i < count)
	{
		cmd_signalhandler(pip->cmd->simple_cmd[0], pip->param->prog);
		if (i != count - 1 && pipe(fd[i]))
			return (perror("pipe:"), closexwait(fd, count, pid));
		pid = fork();
		if (!pid)
		{
			if (i == 0)
				handle_cmd(pip, NULL, fd[i], env);
			else if (i == count - 1)
				handle_cmd(pip, fd[i - 1], NULL, env);
			else
				handle_cmd(pip, fd[i - 1], fd[i], env);
		}
		if (i != count - 1)
			close(fd[i][1]);
		pip = pip->next;
	}
	return (closexwait(fd, count, pid));
}
