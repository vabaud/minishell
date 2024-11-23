/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:15:31 by vabaud            #+#    #+#             */
/*   Updated: 2023/11/08 18:39:27 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applique la fonction 'f' a chaque caractere et
cree une nouvelle chaine avec les resultats */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*nstr;
	size_t	i;
	size_t	size;

	i = 0;
	size = ft_strlen(s);
	nstr = malloc(sizeof(char) * (size + 1));
	if (!nstr)
		return (NULL);
	while (i < size)
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
