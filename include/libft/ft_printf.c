/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:54:08 by vabaud            #+#    #+#             */
/*   Updated: 2024/03/20 13:27:44 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_choice(va_list args, const char str)
{
	int	i;

	i = 0;
	if (str == 'c')
		i += ft_putchar(va_arg(args, int));
	else if (str == 'd' || str == 'i')
		i += ft_putnbr(va_arg(args, int));
	else if (str == '%')
		i += ft_putchar('%');
	else if (str == 'u')
		i += ft_putunsignednbr(va_arg(args, unsigned int));
	else if (str == 's')
		i += ft_putstr(va_arg(args, char *));
	else if (str == 'x')
		i += ft_lowerhex(va_arg(args, unsigned int));
	else if (str == 'X')
		i += ft_upperhex(va_arg(args, unsigned int));
	else if (str == 'p')
		i += ft_pointer(va_arg(args, unsigned long));
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		print_len;

	va_start(args, str);
	print_len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			print_len += ft_choice(args, str[i]);
		}
		else
			print_len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (print_len);
}
