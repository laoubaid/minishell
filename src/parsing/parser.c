/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:09:31 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 19:32:04 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	parser(char *input, t_ast **ast)
{
	t_token	*tokens;

	if (!input)
	{
		rl_clear_history();
		exit(EXIT_SUCCESS);
	}
	if (!*input || all_whitespace(input))
	{
		free(input);
		return (0);
	}
	add_history(input);
	tokens = tokenizer(input);
	if (grammar(tokens))
	{
		clean_tokens(tokens);
		*ast = NULL;
		return (1);
	}
	*ast = build_ast(tokens);
	clean_tokens(tokens);
	return (0);
}
