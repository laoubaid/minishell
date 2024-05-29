/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:09:31 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/29 19:01:34 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parser(char *input)
{
	t_token	*tokens;
	t_ast	*ast;

	if (*input == '\n')
		return (0);
	tokens = tokenizer(input);
	printf("------------------------these are intial tokens------------------------\n");
	print_tokens(tokens);
	printf("-----------------------------------------------------------------------\n\n");
	ast = build_ast(tokens);
	print_ast(ast);
	clean_ast(ast);
	clean_tokens(tokens, 0);
	return (0);
}
