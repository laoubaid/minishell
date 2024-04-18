/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:13:42 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/06 19:22:26 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	cal_len(char *p)
{
	int	i;

	i = 0;
	if (!p)
		return (0);
	while (p[i] && p[i] != '\n')
		i++;
	if (p[i] == '\n')
		i++;
	return (i);
}

void	ft_bzero(void *p, int n)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)p;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*join;

	i = 0;
	if (!s1 && !s2)
		return (0);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	if (s1)
	{
		while (s1[i])
		{
			join[i] = s1[i];
			i++;
		}
		free(s1);
	}
	if (s2)
		while (*s2)
			join[i++] = *s2++;
	join[i] = 0;
	return (join);
}

int	ft_free_cmd(char ***cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		ft_free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	return (0);
}
