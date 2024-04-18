/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/13 12:08:46 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	count_words(char *s)
{
	int	count;
	int	i;
	int	len;

	i = 1;
	count = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((s[i] == 32 || s[i] == '\0') && s[i - 1] != 32)
			count++;
		i++;
	}
	return (count);
}

static char	*count_chars(char *s, int *nbc, int *ns)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (ptr[i] == 32)
		i++;
	while (!(ptr[i] == 32 || ptr[i] == '\0'))
	{
		(*nbc)++;
		i++;
	}
	*ns = *nbc;
	while (ptr[i] == 32)
	{
		i++;
		(*ns)++;
	}
	return (&ptr[i]);
}

char	**ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	**ft_fill(char **ptr, char *s, int nw)
{
	int	i;
	int	nc;
	int	j;
	int	ns;

	i = 0;
	while (i < nw)
	{
		nc = 0;
		ns = 0;
		s = count_chars(s, &nc, &ns);
		ptr[i] = (char *)malloc(nc + 1);
		if (!ptr[i])
			return (ft_free(ptr));
		j = 0;
		while (*(s - ns) != 32 && *(s - ns))
		{
			ptr[i][j++] = *(s - ns);
			ns--;
		}
		ptr[i++][j] = '\0';
	}
	return (ptr);
}

char	**ft_split(char *s)
{
	char	**ptr;
	int		nword;

	if (!s)
		return (0);
	nword = count_words(s);
	ptr = (char **)malloc((nword + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr = ft_fill(ptr, s, nword);
	if (ptr)
		ptr[nword] = (NULL);
	return (ptr);
}
