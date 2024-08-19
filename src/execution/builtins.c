/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:33:33 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/19 17:01:24 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	ft_echo(char **cmd, t_param *param)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (cmd[1] && !ft_strncmp("-n", cmd[1], 2))
	{
		while (cmd[1][i] == 'n')
			i++;
		if (!(cmd[1][i]) && ++flag)
			i = 2;
		else
			i = 1;
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		env_edit(param, "_", cmd[i], 1);
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	
	return (0);
}

void	clean_exit(char *value, char *msg, int exit_status, t_param *param)
{
	if (msg && value)
	{
		write(2, value, ft_strlen(value));
		write(2, msg, ft_strlen(msg));
	}
	//clean param here
	exit(exit_status);
}

int	ft_exit(char **cmd, t_param *param)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		if (ft_strlen(cmd[1]) > 19)
			clean_exit(cmd[1], ": numeric argument required\n", 2, param);
		if (cmd[1][1] == '-' && cmd[1][1] == '+')
			i++;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
				clean_exit(NULL, ": numeric argument required\n", 2, param);
			i++;
		}
		if (!cmd[2])
			clean_exit(NULL, NULL, ft_atoi(cmd[1]), param);
		else
			return (write(2, "exit: too many arguments\n", 25), 1);
	}
	clean_exit(NULL, NULL, 1, param);
	return (1);
}

int ft_env(t_param *param)
{
	char	**tmp;

	tmp = param->env_arr;

	while (*tmp)
	{
		write(1, *tmp, ft_strlen(*tmp));
		write(1, "\n", 1);
		tmp++;
	}
	env_edit(param, "_", "env", 1);
	return (0);
}

int ft_export(t_param *param , char **cmd)
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
		if (!checkifvalid(cmd[i], &i) || checkifexist(cmd[i], param->env, &i))
			continue ;
		tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->name = ft_strdup(cmd[i]);
		tmp->value = env_fetch(tmp->name, tmp);
		i++;
	}
	param->env_arr = recreate_env(param->env, NULL);
	env_edit(param, "_", "export", 1);
	return (0);
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
	if (!ft_strncmp(cmd->simple_cmd[0], "cd", 2))
		exit_status = ft_cd(param, cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "echo", 4))
		exit_status = ft_echo(cmd->simple_cmd, param);
	else if (!ft_strncmp(cmd->simple_cmd[0], "pwd", 3))
		exit_status = ft_pwd(param);
	else if (!ft_strncmp(cmd->simple_cmd[0], "export", 6))
		exit_status = ft_export(param, cmd->simple_cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "unset", 5))
		exit_status = ft_unset(param, cmd->simple_cmd);
	else if (!ft_strncmp(cmd->simple_cmd[0], "env", 3))
		exit_status = ft_env(param);
	else if (!ft_strncmp(cmd->simple_cmd[0], "exit", 4))
		exit_status = ft_exit(cmd->simple_cmd, param);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (close(fd[0]), close(fd[1]), exit_status);
}
