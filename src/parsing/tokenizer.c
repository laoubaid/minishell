/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:51:55 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/11 02:02:33 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

// int		op_char(char c)
// {
// 	if (c == '|' || c == '||' || c == '&&')
// 		return (1);
// 	return (0);
// }

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
	// how to clear input buffer
	// if (exit_process)
	// {
	// 	rl_clear_history();
	// 	exit(exit_process);
	// }
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
		// || *input == '"'
		// || *input == '\'')
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

void	*quote_token(char **input, t_token *last, char quote)
{
	int		len;
	char	*content;

	len = 0;
	(*input)++;
	while ((*input)[len] && (*input)[len] != quote)
		len++;
	if (!(*input)[len])
		content = NULL;
	else
	{
		content = ft_substr(*input, 0, len);
		if (!content)
			return (NULL);
		(*input)++;
	}
	*input += len;
	if (quote == '"')
		last = append_token(last, DQUOTE, content);
	else
		last = append_token(last, SQUOTE, content);
	if (!last)
		free(content);
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
