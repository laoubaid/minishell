/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:49:08 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/22 19:18:16 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*expand_key_ret(char *key, char *value)
{
	free(key);
	return (value);
}

char	*expand_key(char **str, t_param *param, int in)
{
	char	*key;
	int		len;
	t_env	*env;

	len = 0;
	while ((*str)[len] && !is_whitespace((*str)[len]) && (*str)[len] != '$'
		&& (*str)[len] != '"' && (*str)[len] != '\'' && (*str)[len] != '.')
		len++;
	key = ft_substr(*str, 0, len);
	if (!key)
		return (NULL);
	*str += len;
	if ((!*key && in) || (!*key && !in && **str != '"' && **str != '\''))
		return (expand_key_ret(key, ft_strdup("$")));
	if (!ft_strncmp(key, "?", 42))
		return (expand_key_ret(key, ft_itoa(param->exit_status)));
	env = param->env;
	while (env && *key)
	{
		if (!ft_strncmp(key, env->name, len +42))
			return (expand_key_ret(key, ft_strdup(env->value)));
		env = env->next;
	}
	return (expand_key_ret(key, ft_strdup("")));
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
