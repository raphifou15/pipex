/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 18:33:57 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/04 19:12:17 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split2_2(char *str)
{
	char	**tab;
	int		size;
	int		i;

	i = -1;
	size = ft_strlen(str);
	tab = malloc(sizeof(char *) * 2);
	if (tab == NULL)
		return (NULL);
	tab[0] = malloc(sizeof(char) * (size + 1));
	if (tab[0] == NULL)
		return (ft_free2(tab));
	while (str[++i] != '\0')
		tab[0][i] = str[i];
	tab[0][i] = '\0';
	tab[1] = NULL;
	return (tab);
}

char	**ft_split2(char *str)
{
	char	**tab;

	tab = NULL;
	if (str == NULL || str[0] == '\0')
	{
		tab = malloc(sizeof(char *) * 2);
		if (tab == NULL)
			return (NULL);
		tab[0] = malloc(sizeof(char));
		if (tab[0] == NULL)
			return (ft_free2(tab));
		tab[0][0] = '\0';
		tab[1] = NULL;
		return (tab);
	}
	return (ft_split2_2(str));
}
