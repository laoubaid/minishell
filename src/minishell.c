/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/06/07 00:07:44 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	char	*buffer;
	t_ast	*ast;
	int		syntax_error;

	syntax_error = 0;
	shell_signals();
	while (1)
	{
		if (syntax_error)
			buffer = readline("\e[31m➜  \e[36mMiniShell\e[0m ");
		else
			buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
		syntax_error = parser(buffer, ast);
	}
	return (0);
}
