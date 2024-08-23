/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:08:11 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/23 21:20:17 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_redir_no_heredoc(t_param *param, t_redir *current)
{
	char	**expndd_arr;

	expndd_arr = expand_str(current->filename, param);
	if (!expndd_arr)
		return (1);
	if (!expndd_arr[0] || expndd_arr[1])
	{
		free(current->filename);
		free_array(expndd_arr);
		current->filename = NULL;
	}
	else
	{
		free(current->filename);
		current->filename = expndd_arr[0];
		free(expndd_arr);
	}
	return (0);
}

int	expand_heredoc_str(t_redir *current, char **old, char **new)
{
	char	quote;
	int		len;

	len = 0;
	if (**old == '"' || **old == '\'')
	{
		current->expand = 1;
		quote = **old;
		(*old)++;
		while ((*old)[len] != quote)
			len++;
		*new = join_str(*new, ft_substr(*old, 0, len));
		(*old)++;
	}
	else
	{
		while ((*old)[len] && (*old)[len] != '"' && (*old)[len] != '\'')
			len++;
		*new = join_str(*new, ft_substr(*old, 0, len));
	}
	if (!(*new))
		return (1);
	*old += len;
	return (0);
}

int	expand_redir_heredoc(t_redir *current)
{
	char	*new_filename;
	char	*filename;
	char	quote;
	int		len;

	filename = current->filename;
	len = 0;
	new_filename = NULL;
	while (*filename)
	{
		if (expand_heredoc_str(current, &filename, &new_filename))
			return (1);
	}
	free(current->filename);
	current->filename = new_filename;
	return (0);
}

int	expand_redir(t_param *param)
{
	t_redir	*current;

	current = param->ast->cmd->redirs;
	while (current)
	{
		if (current->redir_type != R_HEREDOC)
			if (expand_redir_no_heredoc(param, current))
				return (1);
		if (current->redir_type == R_HEREDOC)
			if (expand_redir_heredoc(current))
				return (1);
		current = current->next;
	}
	return (0);
}
