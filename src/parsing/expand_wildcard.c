/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:41:30 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/24 19:47:24 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	q_matched(char **str, char **pattern)
{
	char	quote;

	if (**pattern == '"' || **pattern == '\'')
	{
		quote = **pattern;
		(*pattern)++;
		while (**pattern != quote)
		{
			if (**str == **pattern)
			{
				(*str)++;
				(*pattern)++;
			}
			else
				return (0);
		}
		if (**pattern == quote)
			(*pattern)++;
		else
			return (0);
	}
	return (1);
}

int	match(char *str, char *pattern)
{
	while (*str || *pattern)
	{
		if (!q_matched(&str, &pattern))
			break ;
		else if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			while (*str && *str != *pattern)
				str++;
		}
		else
		{
			if (*str == *pattern && *str && *pattern)
			{
				str++;
				pattern++;
			}
			else
				break ;
		}
	}
	if (!(*str) && !(*pattern))
		return (1);
	return (0);
}

int	cpy_and_append(char ***arr, char *src)
{
	char	*cpy;

	cpy = ft_strdup(src);
	if (!cpy)
		return (free_array(*arr), 1);
	*arr = array_append(*arr, cpy);
	if (!*arr)
		return (1);
	return (0);
}

DIR	*open_directory(char ***arr, char *str, int *flag)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
	{
		if (cpy_and_append(arr, str))
		{
			*flag = 1;
			return (NULL);
		}
		*flag = 0;
		return (NULL);
	}
	return (dir);
}

int	matched_names(char ***arr, char *str)
{
	DIR				*dir;
	struct dirent	*s_dir;
	int				match_found;
	int				flag;

	match_found = 0;
	dir = open_directory(arr, str, &flag);
	if (!dir)
		return (flag);
	s_dir = readdir(dir);
	while (s_dir)
	{
		if (strncmp(s_dir->d_name, ".", 42) && strncmp(s_dir->d_name, "..", 42)
			&& match(s_dir->d_name, str))
		{
			match_found = 1;
			if (cpy_and_append(arr, s_dir->d_name))
				return (1);
		}
		s_dir = readdir(dir);
	}
	if (!match_found)
		if (cpy_and_append(arr, str))
			return (1);
	return (closedir(dir), 0);
}
