/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/12 14:31:21 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"

int	count_redir(t_redir *tmp, int *in, int *out, int *app)
{
	int	hdoc;

	hdoc = 0;
	while (tmp)
	{
		if (tmp->redir_type == R_STD_OUT)
			(*out)++;
		else if (tmp->redir_type == R_STD_IN)
			(*in)++;
		else if (tmp->redir_type == R_APPEND)
			(*app)++;
		else if (tmp->redir_type == R_HEREDOC)
			hdoc++;
		tmp = tmp->next;
	}
	return (hdoc);
}

int	getfds(int *tab, int i, t_redir *tmp, int flag)
{
	close(tab[i]);
	if (flag == 0)
		tab[i] = open(tmp->filename, O_RDONLY);
	if (flag == 1)
		tab[i] = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (flag == 2)
		tab[i] = open(tmp->filename, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (flag == 3)
		tab[i] = ft_heredoc(tmp->filename);
	if (tab[i] == -1)
	{
		perror("file");
		exit(1);
	}
	return (i + 1);
}

void	duping_suite(int fd, int input, int flag, int hdoc)
{
	if (!flag)
	{
		if (input == 0)
			dup2(fd, STDIN_FILENO);
		else if (hdoc)
			dup2(fd, STDIN_FILENO);
	}
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_duping(t_redir *tmp, int **redirections, int flag, int input)
{
	int	i;
	int	j;
	int	output;

	i = 0;
	j = 0;
	while (tmp)
	{
		output = 0;
		input = 0;
		if (tmp->redir_type == R_STD_IN)
			i = getfds(redirections[0], i, tmp, 0);
		else if (tmp->redir_type == R_STD_OUT && ++output)
			j = getfds(redirections[1], j, tmp, 1);
		else if (tmp->redir_type == R_APPEND && ++output)
			j = getfds(redirections[1], j, tmp, 2);
		else if (tmp->redir_type == R_HEREDOC && flag && ++input && ++input && ++input)
			i = getfds(redirections[0], i, tmp, 3);
		tmp = tmp->next;
	}
	if (i)
		duping_suite(redirections[0][i - 1], input, 0, flag);
	if (output && j)
		duping_suite(redirections[1][j - 1], input, 1, flag);
}

void	redirecte(t_cmd *cmd, int in_count, int out_count,int apd_count)
{
	int		*redirections[2];
	int		hdoc_count;
	int		flag;
	t_redir	*tmp;

	flag = in_count;
	hdoc_count = 0;
	hdoc_count = count_redir(cmd->redirs, &in_count, &out_count, &apd_count);
	redirections[0] = malloc(sizeof(int) * (in_count + hdoc_count));
	redirections[1] = malloc(sizeof(int) * (out_count + apd_count));
	ft_duping(cmd->redirs, redirections, flag, 0);
	free(redirections[0]);
	free(redirections[1]);
}
