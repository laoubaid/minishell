/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:51:55 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/09 23:53:38 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_tokens(t_token *token, int exit_process)
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
	if (exit_process)
		exit(1);
}

t_token	*new_token(t_type type, char *content, t_token *previous)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = content;
	token->type = type;
	token->previous = previous;
	token->next = NULL;
	return (token);
}

void	append_token(t_token *head, t_token **last, t_type type, char *content)
{
	if (*last)
	{
		(*last)->next = new_token(type, content, *last);
		if (!(*last)->next)
			clean_tokens(head, 1);
		*last = (*last)->next;
	}
	else
	{
		*last = new_token(type, content, NULL);
		if (!(*last))
			clean_tokens(head, 1);
	}
}

void	special_token(char **input, t_token *head, t_token **last, t_type type)
{
	append_token(head, last, type, NULL);
	if (type == PIPE || type == GREAT || type == LESS)
		(*input)++;
	else
		(*input) += 2;
}

void	quote_token(char **input, t_token *head, t_token **last, char quote)
{
	int		len;
	char	*content;

	len = 0;
	(*input)++;
	while ((*input)[len] != quote && (*input)[len] != '\n')
		len++;
	if ((*input)[len] == '\n')
		content = NULL;
	else
	{
		content = ft_substr(*input, 0, len);
		if (!content)
			clean_tokens(head, 1);
		(*input)++;
	}
	(*input) += len;
	if (quote == '"')
		append_token(head, last, DQUOTE, content);
	else
		append_token(head, last, SQUOTE, content);
}

void	word_token(char **input, t_token *head, t_token **last)
{
	int		len;
	char	*content;

	len = 0;
	while ((*input)[len] != '\n' && (*input)[len] != ' '
		&& (*input)[len] != '\t')
		len++;
	if (!len)
		return ;
	content = ft_substr(*input, 0, len);
	if (!content)
		clean_tokens(head, 1);
	(*input) += len;
	append_token(head, last, WORD, content);
}

void	get_token(char **input, t_token *tokens, t_token **last)
{
	if (!ft_memcmp(*input, ">>", 2))
		special_token(input, tokens, last, GGREAT);
	else if (!ft_memcmp(*input, "<<", 2))
		special_token(input, tokens, last, LLESS);
	else if (!ft_memcmp(*input, "&&", 2))
		special_token(input, tokens, last, AND);
	else if (!ft_memcmp(*input, "||", 2))
		special_token(input, tokens, last, OR);
	else if (**input == '|')
		special_token(input, tokens, last, PIPE);
	else if (**input == '>')
		special_token(input, tokens, last, GREAT);
	else if (**input == '<')
		special_token(input, tokens, last, LESS);
	else if (**input == '"')
		quote_token(input, tokens, last, '"');
	else if (**input == '\'')
		quote_token(input, tokens, last, '\'');
	else
		word_token(input, tokens, last);
}

// t_token	*tokenizer(char *input)
// {
// 	t_token	*tokens;
// 	t_token	*last;

// 	tokens = NULL;
// 	last = NULL;
// 	while (*input != '\n')
// 	{
// 		while (*input == ' ' || *input == '\t')
// 			input++;
// 		get_token(input, tokens, &last);
// 		if (!tokens)
// 			tokens = last;
// 	}
// 	return (tokens);
// }


t_token	*tokenizer(char *input)
{
	t_token	*tokens;
	t_token	*last;

	tokens = NULL;
	last = NULL;
	while (*input != '\n')
	{
		while (*input == ' ' || *input == '\t')
			input++;
		get_token(&input, tokens, &last);
		if (!tokens)
			tokens = last;

	}
	return (tokens);
}
