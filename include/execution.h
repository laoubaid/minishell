/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:08:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/07/18 02:26:55 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>


int	execute(t_ast *ast, char **env);

char	**split_all(char const *s, char c);
char	**ft_free(char **ptr);

int		path(char ***p, char *ev);
int		getpath(char **ev);

int    test(t_ast *ast, char **env);

#endif