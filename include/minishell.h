/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:32:36 by kez-zoub          #+#    #+#             */
/*   Updated: 2024/08/24 14:28:16 by laoubaid         ###   ########.fr       */
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
#include <dirent.h>

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
	R_STD_IN,
	R_STD_OUT,
	R_APPEND,
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
	int				expand;
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
	char	*prog;
}   t_param;

typedef struct s_pipe  
{
	t_cmd			*cmd;
	t_ast			*node;
	t_param			*param;
	struct s_pipe	*next;
}	t_pipe;

/* signals related functions */
void	shell_signals(void);
void	new_prompt(int signal);
void	new_line(int signal);
void	quit_coredump(int signal);
void	cmd_signalhandler(char *cmd, char *prog);

/* main expande function */
int		expander(t_param	*param);

/* cleaning functions */
void	clean_param(t_param *param);
void	*clean_ast(t_ast *ast);

/* heredoc related functions */
int		heredoc_fetch(t_param *param, int num);
int		heredoc_handler(t_param *param, int num);
char	*ft_heredoc(t_param *param, char *limiter, int num, int flag);
void	redir_heredoc(t_param *param, int num);

#endif
