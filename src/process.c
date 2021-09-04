/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 05:05:17 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/04 21:16:41 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_first_child_process2(char **env, t_pipex *p)
{
	int	fd1;
	int	fd2;

	fd1 = dup2(p->fd[1], STDOUT_FILENO);
	if (fd1 < 0)
		return (good_close(p->open1, p->fd[1], errno));
	fd2 = dup2(p->open1, STDIN_FILENO);
	if (fd2 < 0)
	{
		close(fd1);
		return (good_close(p->open1, p->fd[1], errno));
	}
	close(p->fd[1]);
	close(p->open1);
	execve(p->tab_exe[0], p->tab_exe, env);
	good_close(fd2, fd1, errno);
}

void	make_first_child_process(char **argv, char **env, t_pipex *p)
{
	close(p->fd[0]);
	if (p->cmd1 == NULL || p->cmd1[0] == '\0' || p->cmd1[0] == ' ')
		p->tab_exe = ft_split2(p->cmd1);
	else
		p->tab_exe = ft_split(p->cmd1, ' ');
	if (p->tab_exe == NULL)
	{
		close(p->fd[1]);
		ft_putstr_err("ERROR\nMalloc on p->tab_exe failled\n");
		return ;
	}
	ft_open_file(argv, 1, p);
	if (p->open1 == -1)
		return ;
	check_cmd_contain_path(p->tab_exe[0], p);
	if (p->contain != 1)
	{
		if (join_elem_and_recup(p, p->cmd1) != 0)
			return (good_close(p->open1, p->fd[1], 0));
	}
	if (p->contain == 1 && access(p->tab_exe[0], X_OK) != 0)
		return (good_close(p->open1, p->fd[1], errno));
	make_first_child_process2(env, p);
}

void	make_second_child_process2(char **env, t_pipex *p)
{
	int	fd1;
	int	fd2;

	fd1 = dup2(p->fd[0], STDIN_FILENO);
	if (fd1 < 0)
		return (good_close(p->open2, p->fd[0], errno));
	fd2 = dup2(p->open2, STDOUT_FILENO);
	if (fd2 < 0)
	{
		close(fd2);
		return (good_close(p->open2, p->fd[0], errno));
	}
	close(p->open2);
	close(p->fd[0]);
	execve(p->tab_exe[0], p->tab_exe, env);
	good_close(fd2, fd1, errno);
}

void	make_second_child_process(char **argv, char **env, t_pipex *p)
{
	close(p->fd[1]);
	if (p->cmd2 == NULL || p->cmd2[0] == '\0' || p->cmd2[0] == ' ')
		p->tab_exe = ft_split2(p->cmd2);
	else
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
			return (good_close(p->open2, p->fd[0], 0));
	}
	if (p->contain == 1 && access(p->tab_exe[0], X_OK) != 0)
		return (good_close(p->open2, p->fd[0], errno));
	make_second_child_process2(env, p);
}
