/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_skip.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:39:49 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 19:47:22 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "lexer.h"

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
