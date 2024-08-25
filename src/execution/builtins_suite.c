/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_suite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:21:25 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/23 16:20:34 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	ft_echo(char **cmd)
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
		if (cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	return ((flag || write(1, "\n", 1)), 0);
}

int	ft_pwd(t_param *param)
{
	char	*pwd;
	t_env	*tmp;

	tmp = param->env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = get_env(param, "PWD");
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}

int	ft_cd(t_param *param, t_cmd	*cmd)
{
	if (cmd->simple_cmd[1] && ft_strncmp(cmd->simple_cmd[1], "--", 3))
	{
		if (cmd->simple_cmd[2])
			return (write(2, "cd: too many arguments\n", 23), 1);
		if (chdir_errors(cmd->simple_cmd[1]))
			return (1);
		if (chdir(cmd->simple_cmd[1]) == 0)
		{
			env_edit(param, "OLDPWD", get_env(param, "PWD"), 3);
			return (env_edit(param, "PWD", getcwd(NULL, 0), 3), 0);
		}
	}
	else
	{
		if (getpath(param->env_arr, "HOME=") == -1)
			return (write(2, "cd: HOME not set\n", 17), 1);
		if (!chdir((param->env_arr)[getpath(param->env_arr, "HOME=")] + 5))
		{
			env_edit(param, "OLDPWD", get_env(param, "PWD"), 3);
			return (env_edit(param, "PWD", getcwd(NULL, 0), 3), 0);
		}
	}
	return (perror(cmd->simple_cmd[1]), 1);
}

void	ft_unset_v2(t_param *param, t_env *freeit, t_env *prev)
{
	t_env	*tmp;

	tmp = freeit->next;
	if (freeit == param->env)
		param->env = tmp;
	free(freeit->name);
	free(freeit);
	if (prev)
		prev->next = tmp;
}

int	ft_unset(t_param *param, char **cmd)
{
	int		i;
	t_env	*itrtmp;
	t_env	*prev;

	i = 0;
	prev = NULL;
	while (cmd[i++])
	{
		itrtmp = param->env;
		while (itrtmp)
		{
			if (!ft_strncmp(cmd[i], itrtmp->name, ft_strlen(itrtmp->name) + 1))
			{
				ft_unset_v2(param, itrtmp, prev);
				break ;
			}
			prev = itrtmp;
			itrtmp = itrtmp->next;
		}
	}
	ft_free(param->env_arr);
	param->env_arr = recreate_env(param->env, NULL);
	return (0);
}
