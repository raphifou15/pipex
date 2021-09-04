/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 20:46:29 by rkhelif           #+#    #+#             */
/*   Updated: 2021/09/04 07:26:03 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen2(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && str[i] != c)
		;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *str)
{
	int		i;
	int		size;
	char	*str2;

	if (str == NULL)
		return (NULL);
	i = -1;
	size = ft_strlen(str);
	str2 = (char *)malloc(sizeof(char) * (size + 1));
	if (str2 == NULL)
		return (NULL);
	while (str[++i] != '\0')
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	int		size;
	char	*str2;

	if (str == NULL)
		return (NULL);
	i = -1;
	size = ft_strlen(str) - n;
	str2 = (char *)malloc(sizeof(char) * (size + 1));
	if (str2 == NULL)
		return (NULL);
	while (str[++i + n] != '\0')
		str2[i] = str[i + n];
	str2[i] = '\0';
	return (str2);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
