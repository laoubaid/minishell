/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:45:49 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/23 12:33:20 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	free_array_int(char **arr)
{
	free_array(arr);
	return (1);
}

int	expand_squote(char **str, char **current, char **expdd_arr)
{
	int	len;

	len = 0;
	(*str)++;
	while ((*str)[len] != '\'')
		len++;
	*current = join_str(*current, ft_substr(*str, 0, len));
	if (!(*current))
	{
		free_array(expdd_arr);
		return (1);
	}
	*str += len +1;
	return (0);
}

int	expand_dquote(char **str, t_param *param, char **current, char **arr)
{
	int	len;

	len = 0;
	(*str)++;
	while ((*str)[len] != '"')
	{
		if ((*str)[len] == '$')
		{
			if (len)
				*current = join_str(*current, ft_substr(*str, 0, len));
			*str += len +1;
			if ((len && !(*current))
				|| join_expanded_key(str, current, param, 1))
				return (free_array_int(arr));
			len = 0;
		}
		else
			len++;
	}
	if (len)
		*current = join_str(*current, ft_substr(*str, 0, len));
	if (len && !(*current))
		return (free_array_int(arr));
	*str += len +1;
	return (0);
}

char	**expand_str(char *str, t_param *param)
{
	char	**expdd_arr;
	char	*current;
	int		error;

	expdd_arr = array_join(NULL, NULL);
	if (!expdd_arr)
		return (NULL);
	current = NULL;
	while (*str)
	{
		if (*str == '\'')
			error = expand_squote(&str, &current, expdd_arr);
		else if (*str == '"')
			error = expand_dquote(&str, param, &current, expdd_arr);
		else
			error = expand_noquote(&str, param, &current, &expdd_arr);
		if (error)
			return (NULL);
	}
	if (current)
		expdd_arr = array_append(expdd_arr, current);
	return (expdd_arr);
}
