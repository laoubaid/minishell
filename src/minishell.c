/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 21:43:58 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

int	main(int argc, char **argv, char **env)
{
	char	*buffer;
	t_param *param;
	int		syntax_error;

	syntax_error = 0;
	param = param_init(env);
	if (!param)
		return (1);
	// if param is null (protect!!!)
	param->ast = NULL;// fixed jumb condition (var not initialized error)
	shell_signals();
	while (1)
	{
		buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
		syntax_error = parser(buffer, &(param->ast));
		if (syntax_error)
			continue;
		param->head = param->ast;
		param->exit_status = execute(param);
		printf("----------------------------------------------------------------------\nexit code: %d\n", param->exit_status);
		clean_ast(param->head);
	}
	return (0);
}
