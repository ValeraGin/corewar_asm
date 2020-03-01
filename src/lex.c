/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:41 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 13:36:44 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "error.h"
#include "lexer.h"

t_lexeme	*read_lexems(int fd, const char *filename)
{
	t_lexeme		*list;
	t_lexeme_pos	*pos;
	char			*line;

	pos = init_lexeme_pos(filename, fd);
	list = 0;
	while (get_next_line(fd, &line) == GNL_OK)
	{
		pos->column = 0;
		while (line[pos->column])
		{
			if (skip_whitespaces(line, pos) || skip_comment(line, pos))
				continue;
			add_lexeme(&list, parse_lexeme(&line, pos));
		}
		add_lexeme(&list, init_lexeme(pos, NEWLINE));
		ft_strdel(&line);
		pos->row++;
	}
	add_lexeme(&list, init_lexeme(pos, END));
	return (list);
}
