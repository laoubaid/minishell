/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:34:24 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/11 02:02:33 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**array_append(char **array, char *str)
{
	char	**new_arr;
	int		len;

	len = 0;
	while (array && array[len])
		len++;
	len += 2;
	new_arr = (char **)malloc(sizeof(char *) * len);
	if (!new_arr)
	{
		free(str);
		return (free_array(array));
	}
	len = 0;
	while (array && array[len])
	{
		new_arr[len] = array[len];
		len++;
	}
	new_arr[len] = str;
	len++;
	new_arr[len] = NULL;
	free(array);
	return (new_arr);
}

void	copy_array(char **src, char **dst, int *start)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[*start] = src[i];
		i++;
		(*start)++;
	}
	if (src)
		free(src);
}

char	**array_join(char **array1, char **array2)
{
	char	**new_arr;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	while (array1 && array1[len1])
		len1++;
	while (array2 && array2[len2])
		len2++;
	new_arr = (char **)malloc((len1 + len2 +1) * sizeof(char *));
	if (!new_arr)
	{
		free_array(array1);
		return (free_array(array2));
	}
	len1 = 0;
	copy_array(array1, new_arr, &len1);
	copy_array(array2, new_arr, &len1);
	new_arr[len1] = NULL;
	return (new_arr);
}

char	*join_str(char *str1, char *str2)
{
	char	*joined_str;

	if (!str2)
	{
		if (str1)
			free(str1);
		return (NULL);
	}
	else if (str1)
	{
		joined_str = ft_strjoin(str1, str2);
		free(str1);
		free(str2);
	}
	else
		joined_str = str2;
	return (joined_str);
}

char	*get_env_ret(char *key, char *value)
{
	free(key);
	return (ft_strdup(value));
}

char	*get_env_to_expande(char **str, t_env *env, int in)
{
	char	*key;
	int		len;

	len = 0;
	while ((*str)[len] && !is_whitespace((*str)[len]) && (*str)[len] != '$'
		&& (*str)[len] != '"' && (*str)[len] != '\'')
		len++;
	key = ft_substr(*str, 0, len);
	if (!key)
		return (NULL);
	*str += len;
	if ((!*key && in) || (!*key && !in && **str != '"' && **str != '\''))
		return (get_env_ret(key, "$"));
	while (env && *key)
	{
		if (!ft_strncmp(key, env->name, len +42))
			return (get_env_ret(key, env->value));
		env = env->next;
	}
	return (get_env_ret(key, ""));
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

char	*expand_dquote(char **str, t_env *env, char *current, char **expdd_arr)
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
				return (free_array(expdd_arr));
			*str += len +1;
			current = join_str(current, get_env_to_expande(str, env, 1));
			if (!current)
				return (free_array(expdd_arr));
			len = 0;
		}
		else
			len++;
	}
	current = join_str(current, ft_substr(*str, 0, len));
	if (!current)
		return (free_array(expdd_arr));
	*str += len +1;
	return (current);
}

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

char	*get_nq_str(char **str, t_env *env, char *current, int *len)
{
	char	*noquote_str;

	noquote_str = NULL;
	while ((*str)[*len] && (*str)[*len] != '"' && (*str)[*len] != '\'')
	{
		if ((*str)[*len] == '$')
		{
			noquote_str = join_str(noquote_str, ft_substr(*str, 0, *len));
			if (!noquote_str)
				return (NULL);
			*str += *len +1;
			noquote_str = join_str(noquote_str, get_env_to_expande(str, env, 0));
			if (!noquote_str)
				return (NULL);
			*len = 0;
		}
		else
			(*len)++;
	}
	noquote_str = join_str(noquote_str, ft_substr(*str, 0, *len));
	return (noquote_str);
}

char	*expand_nquote(char **str, t_env *env, char *current, char ***expdd_arr)
{
	char	*noquote_str;
	int		len;

	len = 0;
	noquote_str = get_nq_str(str, env, current, &len);
	if (!noquote_str)
	{
		free(current);
		return (free_array(*expdd_arr));
	}
	current = noquote_split(expdd_arr, current, noquote_str);
	*str += len;
	free(noquote_str);
	return (current);
}

char	**expand_str(char *str, t_env *env)
{
	char	**expdd_arr;
	char	*current;

	expdd_arr = NULL;
	current = NULL;
	while (*str)
	{
		if (*str == '\'')
			current = expand_squote(&str, current, expdd_arr);
		else if (*str == '"')
			current = expand_dquote(&str, env, current, expdd_arr);
		else
			current = expand_nquote(&str, env, current, &expdd_arr);
		if (!current)
			return (NULL);
	}
	if (!expdd_arr && !current)
		return (array_append(expdd_arr, ft_strdup("")));
	expdd_arr = array_append(expdd_arr, current);
	return (expdd_arr);
}

int	expand_args(char ***cmd_arr, t_env *env)
{
	char	**new_cmd_arr;
	char	**expanded;
	char	*str;
	int		i;

	i = 0;
	new_cmd_arr = array_join(NULL, NULL);
	if (!new_cmd_arr)
		return (1);
	while ((*cmd_arr)[i])
	{
		expanded = expand_str((*cmd_arr)[i], env);
		if (!expanded)
			return (1);
		new_cmd_arr = array_join(new_cmd_arr, expanded);
		if (!new_cmd_arr)
			return (1);
		i++;
	}
	free_array(*cmd_arr);
	*cmd_arr = new_cmd_arr;
	return (0);
}

int	expand_redir(t_redir **redirs, t_env *env)
{
	t_redir	*current;
	char	**expndd_arr;

	current = *redirs;
	while (current)
	{
		expndd_arr = expand_str(current->filename, env);
		if (!expndd_arr)
			return (1);
		if (expndd_arr[1])
		{
			free(current->filename);
			free_array(expndd_arr);
			current->filename = NULL;
		}
		else
		{
			free(current->filename);
			current->filename = expndd_arr[0];
			free(expndd_arr);
		}
		current = current->next;
	}
	return (0);
}

void	expand_cmd(t_param	*param)
{
	if (!param || !param->ast || !param->ast->cmd)
		return ;
	if (expand_args(&param->ast->cmd->simple_cmd, param->env))
	{
		// malloc error (how to clean everything up)
		exit(EXIT_FAILURE);
	}
	if (expand_redir(&param->ast->cmd->redirs, param->env))
	{
		// malloc error (how to clean everything up)
		exit(EXIT_FAILURE);
	}
}
