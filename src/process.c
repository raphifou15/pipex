/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 05:05:17 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/03 21:10:14 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    check_cmd_contain_path(char *str, t_pipex *p)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != '\0')
	{
		if (str[i] == '/')
			p->contain = 1;
	}
}


void	ft_open_file(char **argv, int x, t_pipex *p)
{
	int	err;

	if (x == 1)
	{
		p->open1 = open(argv[1], O_RDONLY);
		if (p->open1 == -1)
		{
			err = errno;
			ft_putstr_err(strerror(err));
			ft_putchar_err('\n');
		}
		return ;
	}
	p->open2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (p->open2 == -1)
	{
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
	}
}


char	*join_modif(char *str1, char c, char *str2)
{
	int		size;
	int		i;
	char	*str3;
	int		x;
	
	str3 = NULL;
	i = -1;
	size = ft_strlen(str1);
	size++;
	while (str2[++i] != '\0' && str2[i] != ' ')
		;
	size += i;
	str3 = malloc(sizeof(char) * (size + 1));
	if (str3 == NULL)
		return (NULL);
	i = -1;
	x = -1;
	while (str1[++i] != '\0')
		str3[i] = str1[i];
	str3[i] = c;
	while (str2[++x] != '\0' && str2[x] != ' ')
		str3[++i] = str2[x];
	str3[++i] = '\0';
	return (str3);
}

int	join_elem_and_recup(t_pipex *p, char *str)
{
	int	i;
	int	err;

	i = -1;
	while (p->all_path[++i] != NULL)
	{
		free(p->tab_exe[0]);
		p->tab_exe[0] == NULL;
		p->tab_exe[0] = join_modif(p->all_path[i], '/', str);
		if (p->tab_exe[0] == NULL)
		{
			i = 0;
			ft_putstr("Error\nMalloc on p->tab_exe failled\n");
			while(p->tab_exe[++i] != NULL)
				ft_free(p->tab_exe[i]);
			ft_free(p->tab_exe);
			return (1);
		}
		if (access(p->tab_exe[0], X_OK) == 0)
			return (0);
		err = errno;
	}
	ft_putstr(strerror(err));
	ft_putchar('\n');
	return (1);
}

void	make_first_child_process(char **argv, char **env, t_pipex *p)
{
	int	err;
	int	fd1;
	int	fd2;

	close(p->fd[0]);
	p->tab_exe = ft_split(p->cmd1, ' ');
	if (p->tab_exe == NULL)
	{
		close(p->fd[1]);
		ft_putstr_err("ERROR\nMalloc on p->tab_exe failled\n");
		return ;
	}
	ft_open_file(argv, 1, p);
	if (p->open1 == -1)
		return	;
	check_cmd_contain_path(p->tab_exe[0], p);
	if (p->contain != 1)
	{
		if (join_elem_and_recup(p, p->cmd1) != 0)
		{
			close(p->open1);
			close(p->fd[1]);
			return ;
		}
	}
	if (p->contain == 1 && access(p->tab_exe[0], X_OK) != 0)
	{
		close(p->open1);
		close(p->fd[1]);
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
		return ;
	}
	fd1 = dup2(p->fd[1], STDOUT_FILENO);
	if (fd1 < 0)
	{
		close(p->open1);
		close(p->fd[1]);
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
		return ;
	}
	fd2 = dup2(p->open1, STDIN_FILENO);
	if (fd2 < 0)
	{
		close(fd1);
		close(p->open1);
		close(p->fd[1]);
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
		return ;
	}
	close(p->fd[1]);
	close(p->open1);
	execve(p->tab_exe[0], p->tab_exe, env);
	err = errno;
	ft_putstr(strerror(err));
	ft_putchar('\n');
	close(fd2);
	close(fd1);
}

void	make_second_child_process(char **argv, char **env, t_pipex *p)
{
	int	fd1;
	int	fd2;
	int	err;

	close(p->fd[1]);
	p->tab_exe = ft_split(p->cmd2, ' ');
	if (p->tab_exe == NULL)
	{
		close(p->fd[0]);
		ft_putstr_err("ERROR\nMalloc on p->tab_exe failled\n");
		return ;
	}
	ft_open_file(argv, 0, p);
	if (p->open2 == -1)
		return ;
	check_cmd_contain_path(p->tab_exe[0], p);
	if (p->contain != 1)
	{
		if (join_elem_and_recup(p, p->cmd2) != 0)
		{
			close(p->open2);
			close(p->fd[0]);
			return ;
		}
	}
	if (p->contain == 1 && access(p->tab_exe[0], X_OK) != 0)
	{
		close(p->open2);
		close(p->fd[0]);
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
		return;
	}
	fd1 = dup2(p->fd[0], STDIN_FILENO);
	if (fd1 < 0)
	{
		close(p->open2);
		close(p->fd[0]);
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
		return ;
	}
	fd2 = dup2(p->open2, STDOUT_FILENO);
	if (fd2 < 0)
	{
		close(fd2);
		close(p->open2);
		close(p->fd[0]);
		err = errno;
		ft_putstr(strerror(err));
		ft_putchar('\n');
		return ;

	}
	close(p->open2);
	close(p->fd[0]);
	execve(p->tab_exe[0], p->tab_exe, env);
	err = errno;
	ft_putstr(strerror(err));
	ft_putchar('\n');
	close(fd2);
	close(fd1);
}
