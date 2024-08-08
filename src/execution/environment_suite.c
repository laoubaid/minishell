/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:03:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/07 00:25:26 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

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
			env[i] = strjoin_optclean("=", tmp->value, 0);
			env[i] = strjoin_optclean(tmp->name, env[i], 2);
			i++;
		}
		tmp = tmp->next;
	}
	return (env[i] = NULL, env);
}

int	env_edit(t_param *param, char *find, char *value)
{
	t_env	*tmp;

	tmp = param->env;
	while (tmp)
	{
		if (!ft_strncmp(find, tmp->name, ft_strlen(find)))
		{
			free(tmp->name);
			tmp->name = strjoin_optclean(find, "=", 0);
			tmp->name = strjoin_optclean(tmp->name, value, 3);
			tmp->value = env_fetch(tmp->name, tmp);
			param->env_arr = recreate_env(param->env, NULL);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_variables(t_param *param)
{
	t_env	*tmp;

	tmp = param->env;
	while (tmp)
	{
		if (ft_strncmp("_", tmp->name, 2))
		{
			write(1, tmp->name, ft_strlen(tmp->name));
			if (tmp->value)
			{
				write(1, "=\"", 2);
				write(1, tmp->value, ft_strlen(tmp->value));
				write(1, "\"", 1);
			}
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

int checkifvalid(char *str, int *idx)
{
	char	*tmp;

	tmp = str;
		
	if (!str)
		return ((*idx)++, 0);
	if (!*str || *str == '=' || ft_isdigit(*str))
		return (write(2, "not a valid identifier\n", 23), (*idx)++, 0);
	while (*str && *str != '=')
	{
		if (*str == '+' && *(str + 1) == '=')
			break ;
		if (!ft_isalnum(*str))
			return (write(2, "not a valid identifier\n", 23), (*idx)++, 0);
		str++;
	}
	return (1);
}

char	*checkifexist_suite(char *str, int i, t_env *tmp)
{
	char	*tobefree;

	if (str[i] == '+')
	{
		tobefree = strjoin_optclean("=", tmp->value, 0);
		tobefree = strjoin_optclean(tmp->name, tobefree, 3);
		tobefree = strjoin_optclean(tobefree, str + (i + 2), 1);
	}
	if (str[i] == '=')
	{
		free(tmp->name);
		tobefree = ft_strdup(str);
	}
	return (tobefree);
}

int checkifexist(char *str, t_env *env, int *idx)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		i = ft_strlen(tmp->name);
		if (!ft_strncmp(str, tmp->name, i))
		{
			if (str[i] == '=' || str[i] == '+')
			{
				tmp->name = checkifexist_suite(str, i, tmp);
				tmp->value = env_fetch(tmp->name, tmp);
				return ((*idx)++, 1);
			}
			if (!str[i])
				return ((*idx)++, 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
