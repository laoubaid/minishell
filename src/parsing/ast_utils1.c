/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:52:59 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 20:01:59 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*free_array(char **array)
{
	int	index;

	index = 0;
	if (!array)
		return (NULL);
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
	return (NULL);
}

void	*clean_cmd(t_cmd *cmd)
{
	t_redir	*redirs;
	t_redir	*tmp_redirs;

	free_array(cmd->simple_cmd);
	redirs = cmd->redirs;
	while (redirs)
	{
		tmp_redirs = redirs;
		redirs = redirs->next;
		free(tmp_redirs->filename);
		free(tmp_redirs);
	}
	free(cmd);
	return (NULL);
}

void	*clean_ast(t_ast *ast)
{
	if (!ast)
		return (NULL);
	if (ast->cmd)
		clean_cmd(ast->cmd);
	if (ast->left)
		clean_ast(ast->left);
	if (ast->right)
		clean_ast(ast->right);
	free(ast);
	return (NULL);
}

int	has_redirs(t_token *token)
{
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (!is_words(token))
			return (1);
		token = token->next;
	}
	return (0);
}
