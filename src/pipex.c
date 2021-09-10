/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 16:28:00 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/10 23:35:21 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(void)
{
	t_pipex	*p;

	p = malloc(sizeof(t_pipex));
	if (p == NULL)
		return (NULL);
	p->pid = 0;
	p->cmd1 = NULL;
	p->cmd2 = NULL;
	p->path = NULL;
	p->all_path = NULL;
	p->tab_exe = NULL;
	p->contain = 0;
	return (p);
}

int	recup_value(char **argv, char **env, t_pipex *p)
{
	int	i;

	i = -1;
	p->cmd1 = ft_strdup(argv[2]);
	if (p->cmd1 == NULL)
		return (ft_check_and_free(p, 1) + 1);
	p->cmd2 = ft_strdup(argv[3]);
	if (p->cmd2 == NULL)
		return (ft_check_and_free(p, 2) + 1);
	while (env[++i] != NULL && ft_strncmp(env[i], "PATH", 4) != 0)
		;
	p->path = ft_strndup(env[i], 5);
	if (p->path == NULL)
		return (ft_check_and_free(p, 3) + 1);
	p->all_path = ft_split(p->path, ':');
	if (p->all_path == NULL)
		return (ft_check_and_free(p, 4) + 1);
	return (0);
}

int	ft_pipex(char **argv, char **env, t_pipex *p)
{
	if (recup_value(argv, env, p) != 0)
		return (1);
	if (pipe(p->fd) == -1)
		return (print_error(p, errno));
	p->pid = fork();
	if (p->pid < 0)
		return (print_error(p, errno));
	if (p->pid == 0)
		make_second_child_process(argv, env, p);
	else
	{
		p->pid2 = fork();
		if (p->pid2 == 0)
			make_first_child_process(argv, env, p);
		else
		{
			close(p->fd[1]);
			close(p->fd[0]);
		}
		waitpid(p->pid2, NULL, 0);
	}
	waitpid(p->pid, NULL, 0);
	ft_check_and_free(p, 0);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*p;

	if (check_error(argc) != 0)
		return (0);
	p = init_pipex();
	if (p == NULL)
	{
		ft_putstr_err("Error\nMalloc failled in init_pipex\n");
		return (0);
	}
	if (ft_pipex(argv, env, p) != 0)
		return (0);
	return (0);
}
