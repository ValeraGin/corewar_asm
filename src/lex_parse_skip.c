/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parse_skip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:39:49 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/25 16:25:43 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "lexer.h"

int	skip_whitespaces(int *column, const char *line)
{
	if (is_whitespace(line[*column]))
	{
		while (is_whitespace(line[*column]))
			(*column)++;
		return (1);
	}
	else
		return (0);
}

int		skip_comment(int *column, const char *line)
{
	if (line[*column] == COMMENT_CHAR || line[*column] == ALT_COMMENT_CHAR)
	{
		while (line[*column])
			(*column)++;
		return (1);
	}
	else
		return (0);
}
