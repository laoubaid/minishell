/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:02:33 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/06/05 21:36:46 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quit_shell(int signal)
{
	rl_clear_history();
	exit(0);
}

void	shell_signals(void)
{
	signal(SIGINT, quit_shell);
}
