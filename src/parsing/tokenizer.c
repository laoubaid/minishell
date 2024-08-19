/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:51:55 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 19:42:09 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*special_token(char **input, t_token *last, t_type type)
{
	last = append_token(last, type, NULL);
	if (!last)
		return (NULL);
	if (type == PIPE || type == GREAT || type == LESS
		|| type == RPAREN || type == LPAREN)
		(*input)++;
	else
		(*input) += 2;
	if (type == OR)
		last->prec = 1;
	else if (type == AND)
		last->prec = 1;
	else if (type == PIPE)
		last->prec = 2;
	return (last);
}

int	word_len(char *input)
{
	int		len;
	char	quote;

	len = 0;
	while (input[len] && !is_whitespace(input[len]) && !key_word(&input[len]))
	{
		if (input[len] == '\'' || input[len] == '"')
		{
			quote = input[len];
			len++;
			while (input[len] && input[len] != quote)
				len++;
			if (input[len] != quote)
				return (-1);
			len++;
		}
		else
			len++;
	}
	return (len);
}

void	*word_token(char **input, t_token *last)
{
	int		len;
	char	*content;

	len = word_len(*input);
	if (len == -1)
		content = NULL;
	else
	{
		content = ft_substr(*input, 0, len);
		if (!content)
			return (NULL);
	}
	if (len >= 0)
		(*input) += len;
	else
		while (**input)
			(*input)++;
	last = append_token(last, WORD, content);
	if (!last)
		free(content);
	return (last);
}

void	*get_token(char **input, t_token *last)
{
	if (!ft_memcmp(*input, ">>", 2))
		return (special_token(input, last, DGREAT));
	else if (!ft_memcmp(*input, "<<", 2))
		return (special_token(input, last, DLESS));
	else if (!ft_memcmp(*input, "&&", 2))
		return (special_token(input, last, AND));
	else if (!ft_memcmp(*input, "||", 2))
		return (special_token(input, last, OR));
	else if (**input == '|')
		return (special_token(input, last, PIPE));
	else if (**input == '>')
		return (special_token(input, last, GREAT));
	else if (**input == '<')
		return (special_token(input, last, LESS));
	else if (**input == '(')
		return (special_token(input, last, LPAREN));
	else if (**input == ')')
		return (special_token(input, last, RPAREN));
	else
		return (word_token(input, last));
}

t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	t_token	*last;
	char	*current;

	tokens = NULL;
	last = NULL;
	current = input;
	while (*current)
	{
		while (is_whitespace(*current))
			current++;
		if (!*current)
			break ;
		last = get_token(&current, last);
		if (!last)
		{
			free(input);
			clean_tokens(tokens);
			exit(EXIT_FAILURE);
		}
		if (!tokens)
			tokens = last;
	}
	free(input);
	return (tokens);
}
