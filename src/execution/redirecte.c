/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/23 22:45:48 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

void	redir_heredoc_fetch(t_param *param, int num)
{
	t_redir *tmp;
	int		i;

	i = 1;
	if (!param->ast->cmd)
		return ;
	tmp = param->ast->cmd->redirs;
	while (tmp)
	{
		if (tmp->redir_type == R_HEREDOC)
		{
			free(tmp->filename);
			tmp->filename = strjoin_optclean("/tmp/hdoc", ft_itoa(num * 100 + i), 2);
			tmp->redir_type = R_STD_IN;
			i++;
		}
		tmp = tmp->next;
	}
}

int	heredoc_fetch(t_param *param, int num)
{
	t_ast	*save;
	t_ast	*tmp;

	if (!param->ast)
		return (num);
	save = param->ast;
	tmp = param->ast->right;
	if (param->ast->cmd && param->ast->type != LPAREN)
		redir_heredoc_fetch(param, num);
	if (param->ast->left)
	{
		param->ast = param->ast->left;
		num = heredoc_fetch(param, num);
	}
	if (tmp)
	{
		param->ast = tmp;
		num = heredoc_fetch(param, num);
	}
	tmp = param->ast;
	param->ast = save;
	if (param->ast->type == LPAREN)
		redir_heredoc_fetch(param, num);
	param->ast = tmp;
	return (num + 1);
}

int	heredoc_handler(t_param *param, int num)
{
	t_ast	*save;
	t_ast	*tmp;

	if (!param->ast)
		return (num);
	save = param->ast;
	tmp = param->ast->right;
	if (param->ast->cmd && param->ast->type != LPAREN)
		redir_heredoc(param, num);
	if (param->ast->left)
	{
		param->ast = param->ast->left;
		num = heredoc_handler(param, num);
	}
	if (tmp)
	{
		param->ast = tmp;
		num = heredoc_handler(param, num);
	}
	tmp = param->ast;
	param->ast = save;
	if (param->ast->type == LPAREN)
		redir_heredoc(param, num);
	param->ast = tmp;
	return (num + 1);
}

void	redir_heredoc(t_param *param, int num)
{
	t_redir *tmp;
	int		i;

	i = 1;
	if (!param->ast->cmd)
		return ;
	tmp = param->ast->cmd->redirs;
	expander(param);
	while (tmp)
	{
		if (tmp->redir_type == R_HEREDOC)
		{
			tmp->filename = ft_heredoc(tmp->filename, (num * 100 + i));
			tmp->redir_type = R_STD_IN;
			i++;
		}
		tmp = tmp->next;
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
		if (input > 0)
			dup2(input, STDIN_FILENO);
		if (output > 0)
			dup2(output, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}
