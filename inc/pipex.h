/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:30:51 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/03 20:28:03 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

typedef struct	s_pipex
{
	int		pid;
	int		pid2;
	int		fd[2];
	char	*cmd1;
	char	*cmd2;
	char	*path;
	char	**all_path;
	char	**tab_exe;
	int		open1;
	int		open2;
	int		contain;
}				t_pipex;

int		ft_pipex(char **argv, char **env, t_pipex *p);
t_pipex	*init_pipex(void);
int		recup_value(char **argv, char **env, t_pipex *p);
void    check_cmd_contain_path(char *str, t_pipex *p);


int		check_error(int argc);
//int		check_if_is_file(char *path1, char *path2);
//int		check_arguments(int argc, char **argv);
int		print_error(t_pipex *p, int err);
void	print_msg_error(int err);


int		ft_check_and_free(t_pipex *p, int err);
void	ft_free(void *str);
void    *ft_free2(char **str);

void	make_first_child_process(char **argv, char **env, t_pipex *p);
void    make_second_child_process(char **argv, char **env, t_pipex *p);
int		join_elem_and_recup(t_pipex *p, char *str);
char    *join_modif(char *str1, char c, char *str2);
void	ft_open_file(char **argv, int x, t_pipex *p);

void	ft_putchar(char c);
void	ft_putstr(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strlen2(const char *str, char c);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, int n);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split(const char *str, char c);
void	ft_putchar_err(char c);
void	ft_putstr_err(char *str);
#endif
