/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/07/19 03:22:20 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/execution.h"

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_ast	*ast;
	int		syntax_error;
	int		exit_status;

	syntax_error = 0;
	shell_signals();
	while (1)
	{
		if (syntax_error)
			buffer = readline("\e[31m➜  \e[36mMiniShell\e[0m ");
		else
			buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
		syntax_error = parser(buffer, &ast);
		// print_ast(ast);
		////////////////////////////////////////////////////////i did comment all the info printing in parsing
		exit_status = test(ast, env);
		printf("exit code: %d\n", exit_status);
		// execute(ast, env);
		clean_ast(ast);
	}
	return (0);
}
