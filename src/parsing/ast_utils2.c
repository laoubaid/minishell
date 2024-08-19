/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:01:40 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 20:02:46 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_rediration(t_token *token)
{
	if (token->type == GREAT || token->type == DGREAT
		|| token->type == LESS || token->type == DLESS)
		return (1);
	return (0);
}

int	is_words(t_token *token)
{
	if (token->type == WORD)
		return (1);
	return (0);
}

int	is_op(t_token *token)
{
	if (token->type == PIPE || token->type == OR || token->type == AND)
		return (1);
	return (0);
}

t_ast	*new_ast(t_ast *left, t_ast *right, t_cmd *cmd, t_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
	{
		clean_ast(left);
		clean_ast(right);
		return (NULL);
	}
	ast->type = type;
	ast->left = left;
	ast->right = right;
	ast->cmd = cmd;
	return (ast);
}
