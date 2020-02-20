/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:41 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 14:35:27 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include "error.h"
#include "lexer.h"

int		is_whitespace(char c)
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

int	is_register(const char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) >= 2 && ft_strlen(arg) <= 3 && arg[i] == REG_CHAR)
	{
		i++;
		while (ft_isdigit(arg[i]))
			i++;
		return (!arg[i] && ft_atoi(&arg[1]) > 0);
	}
	return (0);
}

void	skip_whitespaces(int *column, const char *line)
{
	while (is_whitespace(line[*column]))
		(*column)++;
}

void	skip_comment(int *column, const char *line)
{
	if (line[*column] == COMMENT_CHAR
		|| line[*column] == ALT_COMMENT_CHAR)
		while (line[*column] && line[*column] != '\n')
			(*column)++;
}

t_lexeme	*read_lexems(int fd)
{
	t_lexeme	*list;
	char		*line;
	int			row;
	int			column;

	row = 0;
	while (get_next_line(fd, &line) == GNL_OK)
	{
		column = 0;
		skip_whitespaces(&column, line);
		skip_comment(&column, line);
		if (line[column])
			add_lexeme(&list, parse_lexem(&column, line));
		row++;
	}
}
