/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:36 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/20 01:07:15 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include "parser.h"
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

// parsing enums
typedef enum e_type
{
	WORD,
	PIPE,
	AND,
	OR,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	RPAREN,
	LPAREN
}	t_type;

typedef	enum e_redir_type
{
	R_STD_OUT,
	R_APPEND,
	R_STD_IN,
	R_HEREDOC
}	t_redir_type;

// parsing structs
typedef struct s_token
{
	t_type			type;
	char			*content;
	int				prec;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

typedef struct s_redir
{
	t_redir_type	redir_type;
	char			*filename;
	struct s_redir	*previous;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**simple_cmd;
	t_redir	*redirs;
}	t_cmd;

typedef	struct s_ast
{
	t_type			type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd			*cmd;
}	t_ast;

// execution structs
typedef struct s_env
{
	char			*name;
	char			*value;
	int				print_flag;
	struct s_env	*next;
}	t_env;

typedef struct s_param
{
	t_env	*env;
	char	**env_arr;
	t_ast	*ast;
	int		exit_status;
	t_ast	*head;
}   t_param;

typedef struct s_pipe  
{
	t_cmd			*cmd;
	t_ast			*node;
	t_param			*param;
	struct s_pipe	*next;
}	t_pipe;

void	shell_signals(void);

int		expand_cmd(t_param	*param);

void	clean_param(t_param *param);
void	*clean_ast(t_ast *ast);

#endif