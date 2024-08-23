/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:02:33 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/23 23:26:58 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

extern int ctrl_c;

void	cmd_signalhandler(char *cmd, char *prog)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, quit_coredump);
	if (!ft_strncmp(cmd, prog, (ft_strlen(cmd) + 1)))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	quit_coredump(int signal)
{
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	new_line(int signal)
{
	write(1, "\n", 1);
}

void	new_prompt(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	ctrl_c = 130;
}

void    shell_signals(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}
