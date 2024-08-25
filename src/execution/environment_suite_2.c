/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_suite_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:03:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/20 00:56:38 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char	**recreate_env(t_env *env_list, char **env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env_list;
	while (tmp)
	{
		if (tmp->print_flag)
			i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		if (tmp->print_flag)
		{
			env[i] = join_optclean("=", tmp->value, 0);
			env[i] = join_optclean(tmp->name, env[i], 2);
			i++;
		}
		tmp = tmp->next;
	}
	return (env[i] = NULL, env);
}

int	env_edit(t_param *param, char *find, char *value, int flag)
{
	t_env	*tmp;

	tmp = param->env;
	while (tmp)
	{
		if (!ft_strncmp(find, tmp->name, ft_strlen(find) + 1))
		{
			free(tmp->name);
			tmp->name = join_optclean(find, "=", 0);
			tmp->name = join_optclean(tmp->name, value, flag);
			tmp->value = env_fetch(tmp->name, tmp);
			ft_free(param->env_arr);
			param->env_arr = recreate_env(param->env, NULL);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
