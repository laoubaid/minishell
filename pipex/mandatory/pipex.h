/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:58:18 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/14 13:36:42 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>

/* basic libft functions */
int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
void	skip_space(char *ptr, int *index, int *ns, int flag);
void	fill_word(char *s, int ns, char *ptr);
char	**ft_split(char *s);

/* functions for freeing memory */
char	**ft_free(char **ptr);
void	fd_free(int **fd, int ncmd, int trash);
int		ft_free_cmd(char ***cmd);
char	**ft_free_path(char **ptr);

/* functions to handle path */
int		path(char ***p, char *ev);
char	**ft_split_path(char const *s, char c);
int		getpath(char **ev);
char	*join_path_with_cmd(char *s1, char *s2);
int		is_path(char *str);

/* the main functions to handle the pipes and commands */
int		ft_pipex(int files[2], int ncmd, char ***cmd, char **ev);
int		ftclose(int **fd, int n, int op);
int		**allocate_for_pipe(int n);
int		handle_cmd(int *fdin, int *fdout, char **cmd, char **ev);

#endif
