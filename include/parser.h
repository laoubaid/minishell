/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:09:43 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/07 00:20:34 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_type
{
	WORD,
	PIPE,
	AND,
	OR,
	GREAT,
	GGREAT,
	LESS,
	LLESS,
	DQUOTE,
	SQUOTE
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*content;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

int		parser(char *input);
void	clean_tokens(t_token *token, int exit_process);
t_token	*tokenizer(char *input);

#endif