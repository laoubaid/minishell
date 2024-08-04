/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kez-zoub <kez-zoub@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:08:48 by laoubaid          #+#    #+#             */
/*   Updated: 2024/08/02 11:05:15 by kez-zoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/wait.h>
# include <sys/stat.h>

int		command_execution(t_param *param);

char	**split_all(char const *s, char c);
char	**ft_free(char **ptr);

int		path(char ***p, char *ev);
int		getpath(char **ev, char *comp);

void	redirecte(t_cmd *cmd, int in, int out, int apd);

/* builtins functions */
int		ft_pwd(void);
int		ft_cd(t_param *param);
int		ft_echo(char **cmd);
int		ft_unset(t_param *param, char **cmd);

int		builtins(t_param *param);
int		execute(t_param *param);


/* functions to handle file errors */
int		check_if_path(char *cmd);
int		chdir_errors(char *dir);
int		execution_errors(char *cmd);

int		handle_pipe(t_pipe *pip, char **env);
t_pipe	*pipeline(t_ast *ast);

t_param	*param_init(char **env);

char	*strjoin_optclean(char *s1, char *s2, int flag);

/* functions related to environement */
char	*env_fetch(char *var, t_env *tmp);
char	**recreate_env(t_env *env_list, char **env);

#endif