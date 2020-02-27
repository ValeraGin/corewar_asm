/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parse_skip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:39:49 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 19:36:02 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "lexer.h"

int		skip_whitespaces(char *line, t_lexeme_pos *pos)
{
	if (is_whitespace(line[pos->column]))
	{
		while (is_whitespace(line[pos->column]))
			(pos->column)++;
		return (1);
	}
	else
		return (0);
}

int		skip_comment(char *line, t_lexeme_pos *pos)
{
	if (line[pos->column] == COMMENT_CHAR ||
			line[pos->column] == ALT_COMMENT_CHAR)
	{
		while (line[pos->column])
			(pos->column)++;
		return (1);
	}
	else
		return (0);
}
