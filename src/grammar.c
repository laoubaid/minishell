/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:52:40 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/05/29 18:46:03 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	simple_cmd(t_token **token)
{
	if (!*token || (*token)->type != WORD)
		return (1);
	while (*token && ((*token)->type == WORD || (*token)->type == GREAT || (*token)->type == DGREAT || (*token)->type == LESS || (*token)->type == DLESS))
	{
		if ((*token)->type == WORD)
		{
			*token = (*token)->next;
			continue ;
		}
		*token = (*token)->next;
		if (!*token || (*token)->type != WORD)
			return (1);
		*token = (*token)->next;
	}
	return (0);
}

int	full_cmd(t_token **token)
{
	if ((*token) && (*token)->type == LPAREN)
	{
		*token = (*token)->next;
		if (verify_grammar(token) || !*token || (*token)->type != RPAREN)
			return (1);
		*token = (*token)->next;
		return (0);
	}
	else
	{
		return (simple_cmd(token));
	}
}

int	verify_grammar(t_token **token)
{
	if (full_cmd(token))
		return (1);
	if (!*token || (*token)->type == RPAREN)
		return (0);
	if ((*token)->type == PIPE || (*token)->type == AND || (*token)->type == OR)
	{
		*token = (*token)->next;
		return (verify_grammar(token));
	}
}

// int	full_cmd(t_token **token, int paren)
// {
// 	if (simple_cmd(token))
// 		return (1);
// 	while (*token && ((*token)->type == PIPE || (*token)->type == AND || (*token)->type == OR))
// 	{
// 		*token = (*token)->next;
// 		if (simple_cmd(token))
// 			return (1);
// 	}
// 	if (!*token || (paren && (*token)->type == RPAREN))
// 		return (0);
// 	return (1);
// }

// int	verify_grammar(t_token **token, int paren)
// {
// 	if (*token && (*token)->type == LPAREN)
// 	{
// 		*token = (*token)->next;
// 		if (verify_grammar(token, 1))
// 			return (1);
// 		if (*token && (*token)->type == RPAREN)
// 			*token = (*token)->next;
// 		else
// 			return (1);
// 		if (!paren && !*token)
// 			return (0);
// 		if (paren && *token && (*token)->type == RPAREN)
// 			return (0);
// 		if (*token && ((*token)->type == PIPE || (*token)->type == AND || (*token)->type == OR))
// 		{
// 			*token = (*token)->next;
// 			return (verify_grammar(token, paren));
// 		}
// 		return (1);

// 		// if (paren && *token && (*token)->type == RPAREN)
// 		// 	return (0);
// 		// if (*token && ((*token)->type == PIPE || (*token)->type == AND || (*token)->type == OR))
// 		// {
// 		// 	*token = (*token)->next;
// 		// 	return (verify_grammar(token, paren));
// 		// }
// 		// if (!*token)
// 		// 	return (0);
// 		// return (1);
// 	}
// 	else
// 		return (full_cmd(token, paren));
// }