/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:39:18 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/04 16:03:01 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_error(t_pipex *p, int err)
{
	ft_check_and_free(p, 0);
	ft_putstr_err(strerror(err));
	ft_putchar_err('\n');
	return (err);
}

void	print_msg_error(int err)
{
	if (err == 1)
		ft_putstr_err("Error\nMalloc on p->cmd1 failled\n");
	if (err == 2)
		ft_putstr_err("Error\nMalloc on p->cmd2 failled\n");
	if (err == 3)
		ft_putstr_err("Error\nMalloc on p->path failled\n");
	if (err == 3)
		ft_putstr_err("Error\nOr variable path doesn't exist in env\n");
	if (err == 4)
		ft_putstr_err("Error\nMalloc on p->all_path failled\n");
}

int	check_error(int argc)
{
	if (argc != 5)
	{
		ft_putstr_err("Error\nExemple : ");
		ft_putstr_err("./pipex infile ``grep a1'' ``wc -w'' outfile\n");
		return (1);
	}
	return (0);
}

void	good_close(int a, int b, int err)
{
	close(a);
	close(b);
	if (err == 0)
		return ;
	ft_putstr_err(strerror(err));
	ft_putchar_err('\n');
}
