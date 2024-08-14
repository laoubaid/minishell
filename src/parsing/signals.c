/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:02:33 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/14 12:51:29 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	quit_shell(int signal)
{
	rl_clear_history();
	exit(EXIT_SUCCESS);
}

void	shell_signals(void)
{
	// signal(SIGINT, quit_shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
