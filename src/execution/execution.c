/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 20:06:17 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/23 22:22:58 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	cmd_execve(char **cmd, char **env, t_redir *redir)
{
	int exit_status;

	if (!check_if_path(cmd[0]) && getpath(env, "PATH=") != -1)
		path(&cmd, (env)[getpath(env, "PATH=")]);
	redirecte(redir);
	exit_status = execution_errors(cmd[0]);
	if (exit_status)
		exit(exit_status);
	execve(cmd[0], cmd, env);
	if (cmd[0])
		ft_putstr_fd(cmd[0], 2);
	write(2, ": command not found\n", 20);
	exit(127);
}

int	command_execution(t_param *param)
{
	char	**cmd;
	int		exit_status;

	cmd = param->ast->cmd->simple_cmd;
	set_last_arg(param, NULL, cmd);   //potontioal error
	exit_status = builtins(param, param->ast->cmd);
	if (exit_status != -1)
		return (exit_status);
	cmd_signalhandler(cmd[0], param->prog);
	if (!fork())
	{
		cmd_execve(cmd, param->env_arr, param->ast->cmd->redirs);
	}
	wait(&exit_status);
	if (WIFEXITED(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WIFSIGNALED(exit_status))
		return (128 + WTERMSIG(exit_status));
	return (1);
}
