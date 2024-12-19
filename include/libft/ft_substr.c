/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:03:07 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/19 18:43:16 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* La fonction ft_substr est une fonction en C qui extrait une sous-chaîne
à partir d'une chaîne de caractères source s. La sous-chaîne extraite
commence à l'indice start et a une longueur maximale de len caractères */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	s_len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	while (len)
	{
		sub_str[i] = s[start];
		start++;
		i++;
		len--;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
