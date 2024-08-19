/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:56:16 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 19:59:47 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cmd_len(t_token *token)
{
	int	len;

	len = 0;
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (is_words(token))
			len++;
		if (is_rediration(token))
			token = token->next;
		token = token->next;
	}
	return (len);
}

char	**get_simple_cmd(t_token *token)
{
	char	**simple_cmd;
	int		len;

	len = cmd_len(token) +1;
	simple_cmd = (char **)malloc(len * sizeof(char *));
	if (!simple_cmd)
		return (NULL);
	simple_cmd[len -1] = NULL;
	len = 0;
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (is_words(token))
		{
			simple_cmd[len] = ft_strdup(token->content);
			if (!simple_cmd[len])
				return (free_array(simple_cmd));
			len++;
		}
		else
			token = token->next;
		token = token->next;
	}
	return (simple_cmd);
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
	redir->limiter = NULL;
	redir->filename = ft_strdup(token->content);
	if (!(redir->filename))
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

t_redir	*get_redirs(t_token *token)
{
	t_redir	*redirs;
	t_redir	*current;

	redirs = NULL;
	while (token && !is_op(token) && token->type != RPAREN)
	{
		if (!is_words(token))
		{
			if (redirs)
			{
				current->next = new_redir(token, current);
				current = current->next;
			}
			else
			{
				redirs = new_redir(token, NULL);
				current = redirs;
			}
			if (!current)
				return (NULL);
			token = token->next;
		}
		token = token->next;
	}
	return (redirs);
}

t_cmd	*new_cmd(t_token **token)
{
	t_cmd	*cmd;
	int		redirs;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	redirs = has_redirs(*token);
	cmd->simple_cmd = get_simple_cmd(*token);
	if (redirs)
		cmd->redirs = get_redirs(*token);
	else
		cmd->redirs = NULL;
	if (!cmd->simple_cmd || (redirs && !(cmd->redirs)))
		return (clean_cmd(cmd));
	while (*token && !is_op(*token) && (*token)->type != RPAREN)
		*token = (*token)->next;
	return (cmd);
}
