/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:41 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/25 19:47:38 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "error.h"
#include "lexer.h"

t_lexeme	*read_lexems(int fd)
{
	t_lexeme	*list;
	char		*line;
	int			row;
	int			column;

	row = 0;
	list = 0;
	while (get_next_line(fd, &line) == GNL_OK)
	{
		column = 0;
		while (line[column])
		{
			if (skip_whitespaces(&column, line) || skip_comment(&column, line))
				continue;
			add_lexeme(&list, parse_lexeme(fd, row, &column, line));
		}
		add_lexeme(&list, init_lexeme(row, column, NEWLINE));
		ft_strdel(&line);
		row++;
	}
	add_lexeme(&list, init_lexeme(row, column, END));
	return (list);
}
