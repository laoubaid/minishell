/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/04/28 18:49:30 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*buffer;

	while (1)
	{
		ft_putstr_fd("\e[32m➜  \e[36mMiniShell\e[0m ", 1);
		buffer = get_raw_input();
		ft_putstr_fd(buffer, 1);
		free(buffer);
	}
	return (0);
}
