/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:09:43 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/18 23:07:48 by laoubaid         ###   ########.fr       */
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
int		is_words(t_token *token);
int		is_rediration(t_token *token);
int		is_op(t_token *token);
t_ast	*build_ast(t_token *token);
int		verify_grammar(t_token **token);
int		grammar(t_token *token);
t_ast	*fill_branches(int	min_prec, t_token **token);

//to be deleted
void	print_tokens(t_token *tokens);
void	print_cmd(t_cmd *cmd);
void	print_ast(t_ast *ast);

#endif