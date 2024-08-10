/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/10 16:21:37 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/execution.h"

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_param *param;
	int		syntax_error;
	int		exit_status;

	syntax_error = 0;
	param = param_init(env);
	// if param is null (protect!!!)
	param->ast = NULL;// fixed jumb condition (var not initialized error)
	shell_signals();
	while (1)
	{
		if (syntax_error)
			buffer = readline("\e[31m➜  \e[36mMiniShell\e[0m ");
		else
			buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
		syntax_error = parser(buffer, &(param->ast));
		if (syntax_error)
			continue;
		if (param->ast)
		{
			print_ast(param->ast);
			printf("after expansion: \n");
			expand_cmd(param);
			print_ast(param->ast);
		}
		// exit_status = execute(param);
		// printf("----------------------------------------------------------------------\nexit code: %d\n", exit_status);
		param->ast = clean_ast(param->ast);
		// print_ast(param->ast);
		// exit_status = execute(param);
		// printf("----------------------------------------------------------------------\nexit code: %d\n", exit_status);
		// clean_ast(param->ast);
	}
	return (0);
}
