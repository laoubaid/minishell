/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/19 17:01:53 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	heredoc(t_param *param)
{
	t_redir *tmp;
	int		i;

	i = 1;
	tmp = param->ast->cmd->redirs;
	while (tmp)
	{
		if (tmp->redir_type == R_HEREDOC)
		{
			tmp->filename = ft_heredoc(tmp->filename, i);
			tmp->redir_type = R_STD_IN;
			i++;
		}
		tmp = tmp->next;
	}
}

void	pipe_heredoc(t_pipe *pip)
{
	t_pipe	*piptmp;
	t_redir	*tmp;
	int		i;

	i = 1;
	piptmp = pip;
	while (piptmp)
	{
		tmp = piptmp->cmd->redirs;
		while (tmp)
		{
			if (tmp->redir_type == R_HEREDOC)
			{
				tmp->filename = ft_heredoc(tmp->filename, i);
				tmp->redir_type = R_STD_IN;
				i++;
			}
			tmp = tmp->next;
		}
		piptmp = piptmp->next;
	}
}

int	redirecte(t_redir *tmp)
{
	int	output;
	int	input;

	output = 0;
	input = 0;
	while (tmp)
	{
		if (tmp->filename == NULL)
			return (ft_putstr_fd("ambiguous redirect\n", 2), 1);
		if (tmp->redir_type == R_STD_IN)
			input = open(tmp->filename, O_RDONLY);
		else if (tmp->redir_type == R_STD_OUT)
			output = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (tmp->redir_type == R_APPEND)
			output = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (input == -1 || output == -1)
			return (perror(""), 1);
		tmp = tmp->next;
	}
	if (input > 0)
		dup2(input, STDIN_FILENO);
	if (output > 0)
		dup2(output, STDOUT_FILENO);
	return (0);
}
