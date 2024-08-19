/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:19:52 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 20:04:55 by kez-zoub         ###   ########.fr       */
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
