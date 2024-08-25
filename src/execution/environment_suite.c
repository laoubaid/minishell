/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:03:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/20 00:56:38 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

char	*get_env(t_param *param, char *find)
{
	t_env	*tmp;
	char	*res;

	res = NULL;
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

int	checkifvalid(char *str, int *idx, t_param *param)
{
	char	*tmp;

	tmp = str;
	if (!str)
		return ((*idx)++, 0);
	if (!(ft_isalpha(*str) || *str == '_'))
	{
		param->exit_status = 1;
		return (write(2, "not a valid identifier\n", 23), (*idx)++, 0);
	}
	while (*str && *str != '=')
	{
		if (*str == '+' && *(str + 1) == '=')
			break ;
		if (!(ft_isalpha(*str) || *str == '_'))
		{
			param->exit_status = 1;
			return (write(2, "not a valid identifier\n", 23), (*idx)++, 0);
		}
		str++;
	}
	return (1);
}

char	*checkifexist_suite(char *str, int i, t_env *tmp)
{
	char	*tobefree;

	if (str[i] == '+')
	{
		tobefree = join_optclean("=", tmp->value, 0);
		tobefree = join_optclean(tmp->name, tobefree, 3);
		tobefree = join_optclean(tobefree, str + (i + 2), 1);
	}
	if (str[i] == '=')
	{
		free(tmp->name);
		tobefree = ft_strdup(str);
	}
	return (tobefree);
}

int	checkifexist(char *str, t_env *env, int *idx)
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
