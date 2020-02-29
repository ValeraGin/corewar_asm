/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parse_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:41:50 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/29 19:51:51 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

int	is_whitespace(char c)
{
	return (c == '\t' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r' ||
			c == ' ');
}

int	is_delimiter(char c)
{
	return (c == '\0'
			|| c == '\n'
			|| is_whitespace(c)
			|| c == CMD_CHAR
			|| c == '\"'
			|| c == DIRECT_CHAR
			|| c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR
			|| c == ALT_COMMENT_CHAR);
}

int	is_register(const char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) >= 2 && ft_strlen(str) <= 3 && str[i] == REG_CHAR)
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
		return (!str[i] && ft_atoi(&str[1]) > 0);
	}
	return (0);
}
