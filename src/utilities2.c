/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 07:16:10 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/04 07:26:33 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putchar_err(char c)
{
	write(2, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		write(1, &str[i], 1);
}

void	ft_putstr_err(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		write(2, &str[i], 1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		;
	return (i);
}
