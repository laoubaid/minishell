/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:08:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/17 17:00:50 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define BUFFER_SIZE 1

# include <sys/wait.h>
# include <sys/stat.h>

int		command_execution(t_param *param);

char	**split_all(char const *s, char c);
char	**ft_free(char **ptr);

int		path(char ***p, char *ev);
int		getpath(char **ev, char *comp);

void	redirecte(t_redir *redir);

/* diffrent main programme functions */
int	subshell(t_param *param);

/* builtins functions */
int		ft_pwd(t_param *param);
int		ft_cd(t_param *param, t_cmd *cmd);
int		ft_echo(char **cmd);
int		ft_unset(t_param *param, char **cmd);

int		builtins(t_param *param, t_cmd *cmd);
int		execute(t_param *param);


/* functions to handle file errors */
int		check_if_path(char *cmd);
int		chdir_errors(char *dir);
int		execution_errors(char *cmd);

void	free_pipe(t_pipe *pip);
int		handle_pipe(t_pipe *pip, char **env);
t_pipe	*pipeline(t_ast *ast, t_param *param);

t_param	*param_init(char **env);

char	*strjoin_optclean(char *s1, char *s2, int flag);

/* functions related to environement */
int		env_edit(t_param *param, char *find, char *value);
void	print_variables(t_param *param);
int		checkifvalid(char *str, int *idx);
int		checkifexist(char *str, t_env *env, int *idx);
char	*env_fetch(char *var, t_env *tmp);
char	**recreate_env(t_env *env_list, char **env);


char	*ft_heredoc(char *limiter, int num);
void	pipe_heredoc(t_pipe *pip);
void	heredoc(t_param *param);

#endif