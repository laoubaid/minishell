/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/20 01:03:08 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

void	clean_param(t_param *param)
{
	t_env	*tmp;
	t_env	*list;

	list = param->env;
	clean_ast(param->head);
	ft_free(param->env_arr);
	tmp = list;
	while (list)
	{
		tmp = list->next;
		free(list->name);
		free(list);
		list = tmp;
	} 
	free(param);
}

void	shell_level(t_param *param)
{
	t_env	*tmp;
	int		lvl;

	tmp = param->env;
	lvl = 0;
	while (tmp)
	{
		if (!ft_strncmp("SHLVL", tmp->name, 6))
		{
			lvl = ft_atoi(tmp->value);
			lvl++;
		}
		tmp = tmp->next;
	}
	env_edit(param, "SHLVL", ft_itoa(lvl), 3);
}

int	main(int argc, char **argv, char **env)
{
	t_param	*param;
	char	*buffer;
	int		syntax_error;

	syntax_error = 0;
	param = param_init(env);
	if (!param)
		return (1);
	shell_level(param);
	shell_signals();
	while (1)
	{
		buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
		if (!buffer)
			break ;
		syntax_error = parser(buffer, &(param->ast));
		if (syntax_error)
			continue ;
		param->head = param->ast;
		if (param->ast)
			param->exit_status = execute(param);
		param->head = clean_ast(param->head);
		param->ast = NULL;
	}
	return (clean_param(param), 0);
}
