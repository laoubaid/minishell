/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:34:24 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/19 23:08:41 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// int	expand_args(char ***cmd_arr, t_env *env)
int	expand_args(t_param *param)
{
	char	**new_cmd_arr;
	char	**expanded;
	char	*str;
	int		i;

	i = 0;
	new_cmd_arr = array_join(NULL, NULL);
	if (!new_cmd_arr)
		return (1);
	while (param->ast->cmd->simple_cmd[i])
	{
		expanded = expand_str(param->ast->cmd->simple_cmd[i], param);
		if (!expanded)
			return (1);
		new_cmd_arr = array_join(new_cmd_arr, expanded);
		if (!new_cmd_arr)
			return (1);
		i++;
	}
	free_array(param->ast->cmd->simple_cmd);
	param->ast->cmd->simple_cmd = new_cmd_arr;
	return (0);
}

// int	expand_redir(t_redir **redirs, t_env *env)
int	expand_redir(t_param *param)
{
	t_redir	*current;
	char	**expndd_arr;

	current = param->ast->cmd->redirs;
	while (current)
	{
		expndd_arr = expand_str(current->filename, param);
		if (!expndd_arr)
			return (1);
		if (expndd_arr[1])
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
		current = current->next;
	}
	return (0);
}

int	expand_cmd(t_param	*param)
{
	char	**cmd;
	int		flag;

	flag = 0;
	if (!param || !param->ast || !param->ast->cmd)
		return (1);
	if (expand_args(param))
	{
		clean_ast(param->head);
		exit(EXIT_FAILURE);
	}
	if (expand_redir(param))
	{
		clean_ast(param->head);
		exit(EXIT_FAILURE);
	}
	return (0);
}
