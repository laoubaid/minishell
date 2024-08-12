/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:02:33 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/11 02:02:33 by laoubaid         ###   ########.fr       */
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
	signal(SIGINT, quit_shell);
	signal(SIGQUIT, SIG_IGN);
}
