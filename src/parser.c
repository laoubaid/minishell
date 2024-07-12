/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:09:31 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/06/07 00:07:21 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	all_whitespace(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}

int	parser(char *input, t_ast *ast)
{
	t_token	*tokens;
	// t_ast	*ast;

	if (!input)
	{
		rl_clear_history();
		exit(0); 
	}
	if (!*input || all_whitespace(input))
	{
		free(input);
		return (0);
	}
	add_history(input);
	tokens = tokenizer(input);
	printf("------------------------these are intial tokens------------------------\n");
	print_tokens(tokens);
	printf("-----------------------------------------------------------------------\n\n");
	if (grammar(tokens))
	{
		clean_tokens(tokens);
		return (1);
	}
	// printf("%s\n" ,getenv("SHELL"));
	tokens = expand_tokens(tokens);
	// exit if build_ast fails
	ast = build_ast(tokens);
	print_ast(ast);
	// clean_ast(ast);
	clean_tokens(tokens);
	return (0);
}
