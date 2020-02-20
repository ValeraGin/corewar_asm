/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:24:20 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 14:33:18 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include "error.h"
#include "lexer.h"

t_lexeme *parse_number(const char *line, int row, int *column,
							t_type_lexem type)
{
	t_lexeme *lexeme;

	lexeme = init_lexeme(row, (*column), STRING);
	return (lexeme);
}

t_lexeme *parse_string(const char *line, int row, int *column)
{
	t_lexeme *lexeme;

	lexeme = init_lexeme(row, (*column), STRING);
	return (lexeme);
}

t_lexeme *parse_identifier(const char *line, int row, int *column,
							t_type_lexem type)
{
	unsigned start;
	t_lexeme *lexeme;

	start = *column;
	lexeme = init_lexeme(row, (*column)++, type);
	while (line[*column] && ft_strchr(LABEL_CHARS, line[*column]))
		(*column)++;
	if ((*column - start) && line[*column] == LABEL_CHAR && (*column)++)
	{
		lexeme->type = LABEL;
		lexeme->content = ft_strndup(&(line[start]), (*column) - start - 1);
		if (!lexeme->content)
			print_error("error alloc memory", 0);
	}
	else if (((*column) - start) && is_delimiter(line[*column]))
	{
		lexeme->content = ft_strndup(&(line[start]), (*column) - start - 1);
		if (!lexeme->content)
			print_error("error alloc memory", 0);
		if (lexeme->type == INDIRECT)
			lexeme->type = (is_register(lexeme->content)) ? REGISTER : OPERATOR;
	}
	else
		print_error("error lex", 0);
	return (lexeme);
}

t_lexeme *parse_lexeme(int row, int *column, const char *line)
{
	if (line[*column] == SEPARATOR_CHAR && (*column)++)
		return (init_lexeme(row, (*column)++, SEPARATOR));
	else if (line[*column] == CMD_CHAR && (*column)++)
		return (parse_identifier(line, row, *column, COMMAND));
	else if (line[*column] == DIRECT_CHAR && (*column)++)
	{
		if (line[*column] == LABEL_CHAR && (*column)++)
			return (parse_identifier(line, row, *column, DIRECT_LABEL));
		else
			return (parse_number(line, row, *column, DIRECT));
	}
	else if (line[*column] == STRING_CHAR)
		return (parse_string(line, row, *column));
	else if (line[*column] == LABEL_CHAR)
		return (parse_identifier(line, row, *column, INDIRECT_LABEL));
	else
		return (parse_number(line, row, *column, INDIRECT));
}
