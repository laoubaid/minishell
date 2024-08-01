/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:21:25 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/01 01:12:00 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}

int	ft_cd(t_param *param)
{
	if (param->ast->cmd->simple_cmd[1])
	{
		if (param->ast->cmd->simple_cmd[2])
			return (write(2, "cd: too many arguments\n", 23), 1);
		if (chdir_errors(param->ast->cmd->simple_cmd[1]))
			return (1);
		if (chdir(param->ast->cmd->simple_cmd[1]) == 0)
			return (0);
	}
	else
	{
		if (getpath(param->env_arr, "HOME=") == -1)
			return (write(2, "cd: HOME not set\n", 17), 1);
		if (!chdir((param->env_arr)[getpath(param->env_arr, "HOME=")] + 5))
			return (0);
		return (1);
	}
	perror(param->ast->cmd->simple_cmd[1]);
	return (1);
}

void	ft_unset_suite(t_param *param, t_env *env, t_env *tmp)
{
	if (tmp)
		tmp->next = env->next;
	else
		param->env = env->next;
	param->env_arr = recreate_env(param->env, NULL);
	free(env->name);
	free(env);
}

int	ft_unset(t_param *param, char **cmd)
{
	int		i;
	t_env	*env;
	t_env	*tmp;

	i = 1;
	while (cmd[i])
	{
		env = param->env;
		if (!ft_strncmp(cmd[i], env->name, ft_strlen(env->name) + 1))
			ft_unset_suite(param, env, NULL);
		tmp = env;
		while (env->next)
		{
			env = env->next;
			if (!ft_strncmp(cmd[i], env->name, ft_strlen(env->name) + 1))
			{
				ft_unset_suite(param, env, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

int	ft_echo(char **cmd)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (cmd[1])
	{
		if (!ft_strncmp("-n", cmd[1], 3))
		{
			flag = 1;
			i++;
		}
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}
