/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:15:44 by vabaud            #+#    #+#             */
/*   Updated: 2023/11/29 05:03:09 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copie une chaîne de caractères source (src) dans une chaîne de caractères
de destination (dest) tout en spécifiant la 
taille maximale de la destination */

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}
