/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:31:32 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 20:03:19 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*paren_ast(t_token **token)
{
	t_ast	*ast;
	t_ast	*l_ast;

	ast = new_ast(NULL, NULL, NULL, (*token)->type);
	if (!ast)
		return (NULL);
	*token = (*token)->next;
	l_ast = fill_branches(1, token);
	if (!l_ast)
		return (clean_ast(ast));
	*token = (*token)->next;
	ast->left = l_ast;
	if (has_redirs(*token))
	{
		ast->cmd = new_cmd(token);
		if (!ast->cmd)
			return (clean_ast(ast));
	}
	return (ast);
}

t_ast	*make_command(t_token **token)
{
	t_ast	*ast;

	if ((*token)->type == LPAREN)
		ast = paren_ast(token);
	else
	{
		ast = new_ast(NULL, NULL, NULL, WORD);
		if (!ast)
			return (NULL);
		ast->cmd = new_cmd(token);
		if (!(ast->cmd))
			return (clean_ast(ast));
	}
	return (ast);
}

t_ast	*fill_branches(int min_prec, t_token **token)
{
	t_ast	*left;
	t_ast	*right;
	int		next_min_prec;
	t_type	type;

	left = make_command(token);
	if (!left)
		return (NULL);
	while (1)
	{
		if (!*token || !is_op(*token) || (*token)->prec < min_prec)
			break ;
		next_min_prec = (*token)->prec +1;
		type = (*token)->type;
		*token = (*token)->next;
		right = fill_branches(next_min_prec, token);
		if (!right)
			return (clean_ast(left));
		left = new_ast(left, right, NULL, type);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*build_ast(t_token *token)
{
	t_ast	*ast;

	ast = fill_branches(1, &token);
	if (!ast)
	{
		clean_tokens(token);
		exit(EXIT_FAILURE);
	}
	return (ast);
}
