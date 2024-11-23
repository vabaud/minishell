/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:03:19 by vabaud            #+#    #+#             */
/*   Updated: 2023/11/08 18:24:35 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* alloue de la mémoire pour un bloc de données de taille count * size
et initialise toutes les valeurs de ce bloc à zéro */

void	*ft_calloc(size_t count, size_t size)
{
	char	*dst;
	int		total;

	total = count * size;
	dst = malloc(total);
	if (!dst)
		return (NULL);
	ft_bzero(dst, total);
	return ((void *)dst);
}
