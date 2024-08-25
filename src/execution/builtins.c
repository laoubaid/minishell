/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:33:33 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/20 17:06:50 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	clean_exit(char *value, char *msg, int exit_status, t_param *param)
{
	write(2, "exit\n", 5);
	if (msg && value)
	{
		write(2, value, ft_strlen(value));
		write(2, msg, ft_strlen(msg));
	}
	clean_param(param);
	exit(exit_status);
}

int	ft_exit(char **cmd, t_param *param)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i] == ' ')
			i++;
		if (cmd[1][i] == '-' || cmd[1][i] == '+')
			i++;
		while (cmd[1][i] == '0')
			i++;
		if (ft_strlen(cmd[1] + i) > 19)
			clean_exit(cmd[1], ": numeric argument required\n", 2, param);
		while (cmd[1][i])
		{
			if (++i && !ft_isdigit(cmd[1][i - 1]))
				clean_exit(cmd[1], ": numeric argument required\n", 2, param);
		}
		if (!cmd[2])
			clean_exit(NULL, NULL, ft_atoi(cmd[1]), param);
		else
			return (write(2, "exit\nexit: too many arguments\n", 30), 1);
	}
	clean_exit(NULL, NULL, 1, param);
	return (1);
}

int	ft_env(t_param *param)
{
	char	**tmp;

	tmp = param->env_arr;
	while (*tmp)
	{
		write(1, *tmp, ft_strlen(*tmp));
		write(1, "\n", 1);
		tmp++;
	}
	return (0);
}

int	ft_export(t_param *param, char **cmd)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!cmd[1])
		print_variables(param);
	tmp = param->env;
	while (tmp->next)
		tmp = tmp->next;
	while (cmd[i])
	{
		if (!checkifvalid(cmd[i], &i, param)
			|| checkifexist(cmd[i], param->env, &i))
			continue ;
		tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->name = ft_strdup(cmd[i]);
		tmp->value = env_fetch(tmp->name, tmp);
		i++;
	}
	ft_free(param->env_arr);
	param->env_arr = recreate_env(param->env, NULL);
	return (param->exit_status);
}

int	builtins(t_param *param, t_cmd *cmd)
{
	int		fd[2];
	int		exit_status;

	exit_status = -1;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (redirecte(cmd->redirs) == 1)
		return (1);
	if (!ft_strncmp(cmd->simple_cmd[0], "cd", 3))
		exit_status = ft_cd(param, cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "echo", 5))
		exit_status = ft_echo(cmd->simple_cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "pwd", 4))
		exit_status = ft_pwd(param);
	else if (!ft_strncmp(cmd->simple_cmd[0], "export", 7))
		exit_status = ft_export(param, cmd->simple_cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "unset", 6))
		exit_status = ft_unset(param, cmd->simple_cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "env", 4))
		exit_status = ft_env(param);
	else if (!ft_strncmp(cmd->simple_cmd[0], "exit", 5))
		exit_status = ft_exit(cmd->simple_cmd, param);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (close(fd[0]), close(fd[1]), exit_status);
}
