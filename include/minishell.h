/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:37:24 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/11 21:50:09 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

int	main(void);
int	pwd(void);
int	has_unclosed_quotes(char *s);
int has_logical_operators(char *s);
int has_invalid_redirections(char *s);


#endif