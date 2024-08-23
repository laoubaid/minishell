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

char	*get_env(t_param *param, char *find)
{
	t_env	*tmp;
	char	*res;

	tmp = param->env;
	while (tmp)
	{
		if (!ft_strncmp(find, tmp->name, ft_strlen(find) + 1))
		{
			res = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
	return (res);
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
	if (cmd->simple_cmd[1])
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
