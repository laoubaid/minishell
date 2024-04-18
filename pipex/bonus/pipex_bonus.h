/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:58:18 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/14 13:37:26 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>

/* basic libft functions */
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(char *s);
char	*ft_strdup(const char *str);

/* get_next_line main and utils functions and macros*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

char	*ft_strjoin(char *s1, char *s2);
void	ft_bzero(void *p, int n);
int		ft_strlen(const char *str);
int		check(char *p);
int		cal_len(char *p);
char	*get_save(char *str, char *save);
char	*get_lin(char *str);
char	*get_next_line(int fd);
int		get_next(int fd, char **str, char **line);

/* functions to handle path */
char	**ft_split_path(char const *s, char c);
int		path(char ***p, char *ev);
int		getpath(char **ev);
int		is_path(char *str);

/* functions for freeing memory */
char	**ft_free_path(char **ptr);
char	**ft_free(char **ptr);
void	fd_free(int **fd, int ncmd, int trash);
int		ft_free_cmd(char ***cmd);

/* the main functions to handle the pipes and commands */
char	***get_args(int ncmd, char **av, char **env);
char	*ft_strjoin_and_keep(char *s1, char *s2);
int		ft_pipex(int files[2], int ncmd, char ***cmd, char **ev);
int		ftclose(int **fd, int n, int op);
int		**allocate_for_pipe(int n);
int		handle_cmd(int *fdin, int *fdout, char **cmd, char **ev);

#endif
