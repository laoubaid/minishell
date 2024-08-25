/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:02 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/24 16:15:27 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"

int	g_ctrl_c = 0;

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
			break ;
		}
		tmp = tmp->next;
	}
	if (lvl > 999)
	{
		lvl = 1;
		write(2, "warning: shell level too high, resetting to 1\n", 46);
	}
	env_edit(param, "SHLVL", ft_itoa(lvl), 3);
}

int	heredoc_fork(t_param *param)
{
	int	exit_status;

	exit_status = 0;
	signal(SIGINT, new_line);
	if (!fork())
	{
		signal(SIGINT, SIG_DFL);
		heredoc_handler(param, 1);
		exit(0);
	}
	wait(&exit_status);
	if (WIFSIGNALED(exit_status))
	{
		param->exit_status = 130;
		return (130);
	}
	return (0);
}

int	ft_minishell(t_param *param)
{
	char	*buffer;

	buffer = readline("\e[32m➜  \e[36mMiniShell\e[0m ");
	if (g_ctrl_c)
		param->exit_status = g_ctrl_c;
	if (!buffer)
		return (1);
	if (parser(buffer, &(param->ast)))
	{
		param->exit_status = 2;
		return (0);
	}
	param->head = param->ast;
	if (param->ast)
	{
		if (!heredoc_fork(param))
		{
			heredoc_fetch(param, 1);
			param->ast = param->head;
			param->exit_status = execute(param);
		}
	}
	param->head = clean_ast(param->head);
	param->ast = NULL;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_param	*param;
	int		helper;
	int		exit_status;

	(void)argc;
	helper = 0;
	param = param_init(env);
	if (!param)
		return (1);
	param->prog = argv[0];
	shell_level(param);
	while (1)
	{
		shell_signals();
		g_ctrl_c = 0;
		if (ft_minishell(param))
			break ;
	}
	exit_status = param->exit_status;
	clean_param(param);
	ft_putstr_fd("exit\n", 2);
	return (exit_status);
}
