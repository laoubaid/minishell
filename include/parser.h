/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:09:43 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/02 18:28:59 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

int		parser(char *input, t_ast **ast);
void	*clean_tokens(t_token *token);
void	*free_array(char **array);
t_token	*tokenizer(char *input);
int		is_whitespace(char c);
// int		op_char(char c);
void	expand_cmd(t_param	*param);
int		is_words(t_token *token);
int		is_rediration(t_token *token);
int		is_op(t_token *token);
t_ast	*build_ast(t_token *token);
int		verify_grammar(t_token **token);
int		grammar(t_token *token);
void	*clean_ast(t_ast *ast);
t_ast	*fill_branches(int	min_prec, t_token **token);

//to be deleted
void	print_tokens(t_token *tokens);
void	print_cmd(t_cmd *cmd);
void	print_ast(t_ast *ast);

#endif