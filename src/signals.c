/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 00:02:33 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/10 00:04:19 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quit_shell(int signal)
{
	exit(0);
}

void	shell_signals(void)
{
	signal(SIGINT, quit_shell);
}
