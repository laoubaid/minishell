/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:38:13 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 19:39:12 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	*clean_tokens(t_token *token)
{
	t_token	*previous;

	while (token)
	{
		previous = token;
		token = token->next;
		if (previous->content)
			free(previous->content);
		free(previous);
	}
	return (NULL);
}

int	key_word(char *input)
{
	if (!ft_memcmp(input, ">>", 2)
		|| !ft_memcmp(input, "<<", 2)
		|| !ft_memcmp(input, "&&", 2)
		|| !ft_memcmp(input, "||", 2)
		|| *input == '|'
		|| *input == '>'
		|| *input == '<'
		|| *input == '('
		|| *input == ')')
		return (1);
	else
		return (0);
}

t_token	*new_token(t_type type, char *content, t_token *previous)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = content;
	token->prec = 0;
	token->previous = previous;
	token->next = NULL;
	return (token);
}

void	*append_token(t_token *last, t_type type, char *content)
{
	if (last)
	{
		last->next = new_token(type, content, last);
		if (!last->next)
			return (NULL);
		last = last->next;
	}
	else
	{
		last = new_token(type, content, NULL);
		if (!last)
			return (NULL);
	}
	return (last);
}
