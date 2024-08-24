/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:49:08 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/24 15:47:44 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	key_not_finished(char **str, int len)
{
	if ((*str)[len] && !is_whitespace((*str)[len]) && (*str)[len] != '$'
		&& (*str)[len] != '"' && (*str)[len] != '\'' && (*str)[len] != '.'
		&& (*str)[len - 1] != '?')
		return (1);
	return (0);
}

char	*expand_key(char **str, t_param *param, int in)
{
	char	*key;
	int		len;
	t_env	*env;

	len = 0;
	while (key_not_finished(str, len))
		len++;
	key = ft_substr(*str, 0, len);
	if (!key)
		return (NULL);
	*str += len;
	if ((!*key && in) || (!*key && !in && **str != '"' && **str != '\''))
		return (free(key), ft_strdup("$"));
	if (!ft_strncmp(key, "?", 42))
		return (free(key), ft_itoa(param->exit_status));
	env = param->env;
	while (env && *key)
	{
		if (!ft_strncmp(key, env->name, len +42) && env->value)
			return (free(key), ft_strdup(env->value));
		if (!ft_strncmp(key, env->name, len +42) && !env->value)
			return (free(key), ft_strdup(""));
		env = env->next;
	}
	return (free(key), ft_strdup(""));
}

int	join_expanded_key(char **str, char **current, t_param *param, int in)
{
	char	*value;

	value = expand_key(str, param, in);
	if (!value)
	{
		free(*current);
		return (1);
	}
	if (!*value)
	{
		free(value);
		return (0);
	}
	*current = join_str(*current, value);
	if (!(*current))
		return (1);
	return (0);
}
