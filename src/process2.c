/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 04:39:29 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/04 04:51:40 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_cmd_contain_path(char *str, t_pipex *p)
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
			while (p->tab_exe[++i] != NULL)
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
