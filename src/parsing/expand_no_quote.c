/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:14:45 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/22 15:37:13 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*nq_ws_found(char ***expdd_arr, char *current, char *ws, int len)
{
	while (*ws)
	{
		*expdd_arr = array_append(*expdd_arr, current);
		current = NULL;
		if (!(*expdd_arr))
			return (NULL);
		while (is_whitespace(*ws))
			ws++;
		while (ws[len] && !is_whitespace(ws[len]))
			len++;
		if (len)
		{
			current = ft_substr(ws, 0, len);
			if (!current)
				return (free_array(*expdd_arr));
			ws += len;
			len = 0;
		}
	}
	return (current);
}

// this function takes the str we made so far and adds on it from the 
// whitespaced str (that we made by expanding the string outside the 
// quotes) and each time we encouter a whitespace the string get added 
// to the array of strings then we start creating a new string after 
// the whitespace
char	*noquote_split(char ***expdd_arr, char *current, char *whitespaced)
{
	int	len;

	len = 0;
	while (whitespaced[len] && !is_whitespace(whitespaced[len]))
		len++;
	if (len)
	{
		current = join_str(current, ft_substr(whitespaced, 0, len));
		if (!current)
			return (free_array(*expdd_arr));
		whitespaced += len;
		len = 0;
	}
	// case whitespace found
	current = nq_ws_found(expdd_arr, current, whitespaced, len);
	return (current);
}

int	get_nq_str(char **str, char **noquote_str, t_param *param, int *len)
{
	*noquote_str = NULL;
	while ((*str)[*len] && (*str)[*len] != '"' && (*str)[*len] != '\'')
	{
		if ((*str)[*len] == '$')
		{
			if (*len)
				*noquote_str = join_str(*noquote_str, ft_substr(*str, 0, *len));
			if (*len && !(*noquote_str))
				return (1);
			*str += *len +1;
			if (join_expanded_key(str, noquote_str, param, 0))
				return (1);
			*len = 0;
		}
		else
			(*len)++;
	}
	if (*len)
		*noquote_str = join_str(*noquote_str, ft_substr(*str, 0, *len));
	if (*len && !(*noquote_str))
		return (1);
	return (0);
}

int	expand_noquote(char **str, t_param *param, char **current, char ***arr)
{
	char	*noquote_str;
	int		len;

	len = 0;
	if (get_nq_str(str, &noquote_str, param, &len))
	{
		free(*current);
		free_array(*arr);
		return (1);
	}
	if (noquote_str)
		*current = noquote_split(arr, *current, noquote_str);
	*str += len;
	free(noquote_str);
	return (0);
}
