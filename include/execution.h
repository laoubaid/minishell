/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:08:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/23 20:27:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define BUFFER_SIZE 1

# include <sys/wait.h>
# include <sys/stat.h>

char	**split_all(char const *s, char c);
char	**ft_free(char **ptr);

int		path(char ***p, char *ev);
int		getpath(char **ev, char *comp);

int		redirecte(t_redir *redir);

/* execution paths related functions */
t_pipe	*pipeline(t_ast *ast, t_param *param);
int		subshell(t_param *param);
int		openfiles(t_param *param);

/* builtins functions */
int		ft_pwd(t_param *param);
int		ft_cd(t_param *param, t_cmd *cmd);
int		ft_echo(char **cmd);
int		ft_unset(t_param *param, char **cmd);

void	cmd_execve(char **cmd, char **env, t_redir *redir);
int		command_execution(t_param *param);

int		builtins(t_param *param, t_cmd *cmd);
int		execute(t_param *param);

/* functions to handle file errors */
int		check_if_path(char *cmd);
int		chdir_errors(char *dir);
int		execution_errors(char *cmd);

/* pipe handling related functions*/
void	pipe_init(t_param *param, t_ast *ast, t_pipe *pip);
int		**ft_pipe_allocatexfree(t_pipe *pip, int *n, int flag);
int		closexwait(int **fd, int count, int pid);
void	handle_cmd(t_pipe *pip, int *fdin, int *fdout, char **env);
int		handle_pipe(t_pipe *pip, char **env, int i, int pid);

t_param	*param_init(char **env);

char	*join_optclean(char *s1, char *s2, int flag);
void	set_last_arg(t_param *param, char *str, char **arr);

/* environement related functions*/
char	*get_env(t_param *param, char *find);
int		env_edit(t_param *param, char *find, char *value, int flag);
void	print_variables(t_param *param);
int		checkifvalid(char *str, int *idx, t_param *param);
int		checkifexist(char *str, t_env *env, int *idx);
char	*env_fetch(char *var, t_env *tmp);
char	**recreate_env(t_env *env_list, char **env);

#endif