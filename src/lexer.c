/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:41 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/19 18:42:56 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"

int		is_whitespace(int c)
{
	return (c == '\t' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r' ||
			c == ' ');
}

void	skip_whitespaces(int *column, const char *line)
{
	while (is_whitespace(row[parser->column]))
		parser->column++;
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
	char	*line;
	int		row;
	int		column;
	
	row = 0;
	while (get_next_line(fd, &line) == GNL_OK)
	{
		column = 0;



		row++;
	}
}