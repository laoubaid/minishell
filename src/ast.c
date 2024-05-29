/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:31:32 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/29 19:02:05 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*clean_cmd(t_cmd *cmd)
{
	t_param	*params;
	t_param	*tmp_params;
	t_redir	*redirs;
	t_redir	*tmp_redirs;

	params = cmd->params;
	redirs = cmd->redirs;
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	while (params)
	{
		tmp_params = params;
		params = params->next;
		free(tmp_params->param);
		free(tmp_params);
	}
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

t_ast	*new_ast(t_ast *left, t_ast *right, t_cmd *cmd, t_type type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->left = left;
	ast->right = right;
	ast->cmd = cmd;
	return (ast);
}

int	has_params(t_token *token)
{
	while (token && token->type != PIPE && token->type != AND && token->type != OR && token->type != RPAREN)
	{
		if (token->type == WORD)
			return (1);
		token = token->next;
		token = token->next;
	}
	return (0);
}

t_param	*new_param(t_token *token, t_param *previous)
{
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		return (NULL);
	param->previous = previous;
	param->next = NULL;
	param->param = ft_strdup(token->content);
	if (!(param->param))
	{
		free(param);
		return (NULL);
	}
	if (param->param[0] == '-')
		param->type = OPTION;
	else
		param->type = ARG;
	return (param);
}

t_param	*get_params(t_token *token)
{
	t_param	*params;
	t_param	*current;

	params = NULL;
	while (token && token->type != PIPE && token->type != AND && token->type != OR && token->type != RPAREN)
	{
		if (token->type == WORD)
		{
			if (params)
			{
				current->next = new_param(token, current);
				if (!(current->next))
					return (NULL);
				current = current->next;
			}
			else
			{
				params = new_param(token, NULL);
				if (!params)
					return (NULL);
				current = params;
			}
		}
		else
			token = token->next;
		token = token->next;
	}
	return (params);
}

int	has_redirs(t_token *token)
{
	while (token && token->type != PIPE && token->type != AND && token->type != OR && token->type != RPAREN)
	{
		if (token->type != WORD)
			return (1);
		token = token->next;
	}
	return (0);
}

t_redir	*new_redir(t_token *token, t_redir *previous)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->previous = previous;
	redir->next = NULL;
	if (token->type == GREAT)
		redir->redir_type = R_STD_OUT;
	else if (token->type == LESS)
		redir->redir_type = R_STD_IN;
	else if (token->type == DGREAT)
		redir->redir_type = R_APPEND;
	else if (token->type == DLESS)
		redir->redir_type = R_HEREDOC;
	token = token->next;
	redir->filename = ft_strdup(token->content);
	if (!(redir->filename))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

t_redir	*get_redirs(t_token **token)
{
	t_redir	*redirs;
	t_redir	*current;

	redirs = NULL;
	while (*token && (*token)->type != PIPE && (*token)->type != AND && (*token)->type != OR && (*token)->type != RPAREN)
	{
		if ((*token)->type != WORD)
		{
			if (redirs)
			{
				current->next = new_redir(*token, current);
				current = current->next;
			}
			else
			{
				redirs = new_redir(*token, NULL);
				current = redirs;
			}
			if (!current)
				return (NULL);
			*token = (*token)->next;
		}
		*token = (*token)->next;
	}
	return (redirs);
}

t_cmd	*new_cmd(t_token **token)
{
	t_cmd	*cmd;
	int		params;
	int		redirs;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_name = ft_strdup((*token)->content);
	*token = (*token)->next;
	params = has_params(*token);
	redirs = has_redirs(*token);
	if (params)
		cmd->params = get_params(*token);
	else
		cmd->params = NULL;
	if (redirs)
		cmd->redirs = get_redirs(token);
	else
		cmd->redirs = NULL;
	if (!(cmd->cmd_name) || (params && !(cmd->params)) || (redirs && !(cmd->redirs)))
		return (clean_cmd(cmd));
	return (cmd);
}

t_ast	*make_command(t_token **token)
{
	t_ast	*ast;

	if ((*token)->type == LPAREN)
	{
		*token = (*token)->next;
		ast = fill_branches(1, token);
		*token = (*token)->next;
	}
	else if ((*token)->type == WORD)
	{
		ast = new_ast(NULL, NULL, NULL, -1);
		ast->cmd = new_cmd(token);
		if (!(ast->cmd))
			return (NULL);
	}
	else
	{
		ft_putstr_fd("Unexpected error\n", 2);
		return (NULL);
	}
	if (!ast)
		return (NULL);
	return (ast);
}

t_ast	*fill_branches(int	min_prec, t_token **token)
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
		if (!*token || ((*token)->type != PIPE && (*token)->type != AND && (*token)->type != OR) || (*token)->prec < min_prec)
			break ;
		next_min_prec = (*token)->prec +1;
		type = (*token)->type;
		*token = (*token)->next;
		right = fill_branches(next_min_prec, token);
		if (!right)
			return (NULL);
		left = new_ast(left, right, NULL, type);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_ast	*build_ast(t_token *token)
{
	t_token	*grammar;

	grammar = token;
	if (verify_grammar(&grammar) || grammar)
	{
		ft_putstr_fd("\e[31mparsing problem\e[0m\n", 2);
		return (NULL);
	}
	else
		printf("\e[32mgrammar is all good\e[0m\n\n");
	return (fill_branches(1, &token));
}
