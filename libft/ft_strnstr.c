/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:15:21 by vabaud            #+#    #+#             */
/*   Updated: 2023/11/08 18:01:37 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* recherche la première occurrence d'une sous-chaîne s2 dans une chaîne s1 */

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*a;

	a = (char *)s1;
	s2_len = 0;
	while (s2[s2_len])
		s2_len++;
	if (s2_len == 0)
		return (a);
	i = 0;
	while (a[i] && i < len)
	{
		j = 0;
		while (a[i + j] && s2[j] && a[i + j] == s2[j] && i + j < len)
			j++;
		if (j == s2_len)
		{
			return (a + i);
		}
		i++;
	}
	return (NULL);
}
