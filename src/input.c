/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:11:59 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/04/28 18:47:14 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*add_char_to_str(char *str, char c)
{
	int		str_len;
	char	*new_str;

	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			exit(1);
	}
	str_len = ft_strlen(str);
	new_str = (char *)malloc(str_len +2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new_str, str, str_len +1);
	new_str[str_len] = c;
	str_len++;
	new_str[str_len] = 0;
	free(str);
	return (new_str);
}

char	*get_raw_input(void)
{
	int		char_read;
	char	buffer;
	char	*str;

	str = NULL;
	buffer = 0;
	char_read = 1;
	while (char_read > 0)
	{
		char_read = read(0, &buffer, 1);
		if (char_read < 0)
		{
			free(str);
			exit(1);
		}
		str = add_char_to_str(str, buffer);
		if (!str)
			exit(1);
		if (buffer == '\n')
			break ;
	}
	return (str);
}
