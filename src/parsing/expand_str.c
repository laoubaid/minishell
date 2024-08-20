/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:45:49 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 23:05:19 by laoubaid         ###   ########.fr       */
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
		&& (*str)[len] != '"' && (*str)[len] != '\'')
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

char	*expand_squote(char **str, char *current, char **expdd_arr)
{
	int	len;

	len = 0;
	(*str)++;
	while ((*str)[len] != '\'')
		len++;
	current = join_str(current, ft_substr(*str, 0, len));
	if (!current)
		return (free_array(expdd_arr));
	*str += len +1;
	return (current);
}

char	*expand_dquote(char **str, t_param *param, char *current, char **arr)
{
	int	len;

	len = 0;
	(*str)++;
	while ((*str)[len] != '"')
	{
		if ((*str)[len] == '$')
		{
			current = join_str(current, ft_substr(*str, 0, len));
			if (!current)
				return (free_array(arr));
			*str += len +1;
			current = join_str(current, expand_key(str, param, 1));
			if (!current)
				return (free_array(arr));
			len = 0;
		}
		else
			len++;
	}
	current = join_str(current, ft_substr(*str, 0, len));
	if (!current)
		return (free_array(arr));
	*str += len +1;
	return (current);
}

char	**expand_str(char *str, t_param *param)
{
	char	**expdd_arr;
	char	*current;

	expdd_arr = NULL;
	current = ft_strdup("");
	if (!current)
		return (NULL);
	while (*str)
	{
		if (*str == '\'')
			current = expand_squote(&str, current, expdd_arr);
		else if (*str == '"')
			current = expand_dquote(&str, param, current, expdd_arr);
		else
			current = expand_noquote(&str, param, current, &expdd_arr);
		if (!current)
			return (NULL);
	}
	expdd_arr = array_append(expdd_arr, current);
	return (expdd_arr);
}
