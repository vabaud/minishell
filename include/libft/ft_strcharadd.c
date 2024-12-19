/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcharadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:55:04 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/19 18:43:06 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcharadd_first(char c)
{
	char	*add;

	add = (char *)malloc(sizeof(char) * 2);
	if (!add)
	{
		ft_printf("ERREUR D'ALLOCATION MEMOIRE\n");
		return (NULL);
	}
	add[0] = c;
	add[1] = '\0';
	return (add);
}

char	*ft_strcharadd(char *str, char c)
{
	char	*add;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_strcharadd_first(c));
	add = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!add)
	{
		ft_printf("ERREUR D'ALLOCATION\n");
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		add[i] = str[i];
		i++;
	}
	free(str);
	add[i++] = c;
	add[i] = '\0';
	return (add);
}
