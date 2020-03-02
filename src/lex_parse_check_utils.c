/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parse_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:41:50 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/02 21:05:08 by hmathew          ###   ########.fr       */
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
	int len;
	int	i;

	len = ft_strlen(str);
	if (str[0] == REG_CHAR && (len == 2 || len == 3))
	{
		i = 0;
		while (++i < len)
			if (!ft_isdigit(str[i]))
				return (0);
		return (1);
	}
	return (0);
}
