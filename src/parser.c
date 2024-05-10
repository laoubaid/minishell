/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:09:31 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/10 00:02:23 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// to be deleted
void	print_tokens(t_token *tokens)
{
	int	id = 1;
	while (tokens)
	{
		printf("token: %d | type: ", id);
		if (tokens->type == WORD)
			printf("WORD | ");
		else if (tokens->type == PIPE)
			printf("PIPE | ");
		else if (tokens->type == AND)
			printf("AND | ");
		else if (tokens->type == OR)
			printf("OR | ");
		else if (tokens->type == GREAT)
			printf("GREAT | ");
		else if (tokens->type == GGREAT)
			printf("GGREAT | ");
		else if (tokens->type == LESS)
			printf("LESS | ");
		else if (tokens->type == LLESS)
			printf("LLESS | ");
		else if (tokens->type == DQUOTE)
			printf("DQUOTE | ");
		else if (tokens->type == SQUOTE)
			printf("SQUOTE | ");
		if (tokens->content)
			printf("content: %s\n", tokens->content);
		else
			printf("content: NULL\n");
		tokens = tokens->next;
		id++;
	}
}
// to be deleted

int	parser(char *input)
{
	t_token	*tokens;

	tokens = tokenizer(input);
	print_tokens(tokens);
	clean_tokens(tokens, 0);
	return (0);
}
