/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:09:43 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 20:09:12 by kez-zoub         ###   ########.fr       */
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
int		key_word(char *input);
void	*append_token(t_token *last, t_type type, char *content);
char	*join_str(char *str1, char *str2);
char	**array_append(char **array, char *str);
char	**array_join(char **array1, char **array2);
char	*expand_noquote(char **str, t_param *param, char *current, char ***expdd_arr);
char	*expand_key(char **str, t_param *param, int in);
char	**expand_str(char *str, t_param *param);
void	expand_cmd(t_param	*param);
int		is_words(t_token *token);
int		is_rediration(t_token *token);
int		is_op(t_token *token);
t_ast	*new_ast(t_ast *left, t_ast *right, t_cmd *cmd, t_type type);
int		has_redirs(t_token *token);
t_cmd	*new_cmd(t_token **token);
t_ast	*build_ast(t_token *token);
int		verify_grammar(t_token **token);
int		grammar(t_token *token);
void	*clean_cmd(t_cmd *cmd);
void	*clean_ast(t_ast *ast);
t_ast	*fill_branches(int	min_prec, t_token **token);

//to be deleted
void	print_tokens(t_token *tokens);
void	print_cmd(t_cmd *cmd);
void	print_ast(t_ast *ast);

#endif