/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:07:43 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/23 23:19:17 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	handle_operations(t_param *param)
{
	t_ast	*tmp;

	tmp = param->ast->right;
	if (param->ast->type == OR)
	{
		param->ast = param->ast->left;
		if (execute(param) != 0)
		{
			param->ast = tmp;
			param->exit_status = execute(param);
		}
	}
	else
	{
		param->ast = param->ast->left;
		if (execute(param) == 0)
		{
			param->ast = tmp;
			param->exit_status = execute(param);
		}
	}
	return (param->exit_status);
}

int	subshell(t_param *param)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if (!pid)
	{
		if (param->ast->cmd != NULL)
			redirecte(param->ast->cmd->redirs);
		param->ast = param->ast->left;
		exit(execute(param));
	}
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (1);
}

t_pipe	*pipeline(t_ast *ast, t_param *param)
{
	t_pipe	*pip;
	t_pipe	*tmp;

	if (ast->left->type == PIPE)
		pip = pipeline(ast->left, param);
	else
	{
		pip = malloc(sizeof(t_pipe));
		pipe_init(param, ast->left, pip);
	}
	tmp = pip;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_pipe));
	tmp = tmp->next;
	pipe_init(param, ast->right, tmp);
	return (pip);
}

int	openfiles(t_param *param)
{
	int	exit_status;

	expander(param);
	if (!fork())
	{
		exit_status = redirecte(param->ast->cmd->redirs);
		clean_param(param);
		exit(exit_status);
	}
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	return (1);
}

int	execute(t_param *param)
{
	int		error;
	t_pipe	*pip;

	error = 0;
	if (param->ast->type == OR || param->ast->type == AND)
		param->exit_status = handle_operations(param);
	else if (param->ast->type == PIPE)
	{
		pip = pipeline(param->ast, param);
		param->exit_status = handle_pipe(pip, param->env_arr, -1, 0);
		ft_pipe_allocatexfree(pip, NULL, 1);
	}
	else if (param->ast->type == LPAREN)
		param->exit_status = subshell(param);
	else if (param->ast->cmd->simple_cmd[0])
	{
		error = expander(param);
		if (!param->ast->cmd->simple_cmd[0])
			param->exit_status = 0;
		else if (!error)
			param->exit_status = command_execution(param);
	}
	else
		param->exit_status = openfiles(param);
	return (param->exit_status);
}
