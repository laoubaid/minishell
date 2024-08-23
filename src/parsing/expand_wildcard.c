/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:41:30 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/23 13:34:43 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	match(char *str, char *pattern)
{
	while (*str && *pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			while (*str && *str != *pattern)
				str++;
		}
		else
		{
			if (*str == *pattern)
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

int	matched_names(char ***arr, char *str)
{
	DIR				*dir;
	struct dirent	*s_dir;
	int				match_found;

	dir = opendir(".");
	match_found = 0;
	if (!dir)
		return (1);
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
	closedir(dir);
}
