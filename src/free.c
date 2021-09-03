/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 03:16:50 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/02 02:11:43 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(void *str)
{
	free(str);
	str = NULL;
}

void	*ft_free2(char **str)
{
	int	i;

	i = -1;
	while (str != NULL && str[++i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
	}
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (NULL);
}

int	ft_check_and_free(t_pipex *p, int err)
{
	int	i;

	i = -1;
	print_msg_error(err);
	if (p->cmd1 != NULL)
		ft_free(p->cmd1);
	if (p->cmd2 != NULL)
		ft_free(p->cmd2);
	if (p->path != NULL)
		ft_free(p->path);
	while (p->all_path != NULL && p->all_path[++i] != NULL)
		ft_free(p->all_path[i]);
	if (p->all_path != NULL)
		free(p->all_path);
	i = -1;
	while (p->tab_exe != NULL && p->tab_exe[++i] != NULL)
		free(p->tab_exe[i]);
	if (p->tab_exe != NULL)
		free(p->tab_exe);
	free(p);
	return (0);
}
