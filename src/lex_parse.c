/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:24:20 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/22 22:01:58 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include "error.h"
#include "lexer.h"

int		parse_integer(const char *str, int *i)
{
	int nbr;
	int nbrtemp;

	nbr = 0;
	nbrtemp = 0;
	while (ft_isdigit(str[*i]))
	{
		nbrtemp = nbr * 10 + (str[(*i)++] - '0');
		if (nbrtemp < nbr)
			return (-1);
		nbr = nbrtemp;
	}
	return (nbr);
}

t_lexeme *parse_number(const char *line, int row, int *column,
							t_type_lexem type)
{
	unsigned start;
	t_lexeme *lexeme;
	int sign;
	int res;

	lexeme = init_lexeme(row, (*column), type);
	start = (*column);
	sign = 0;
	if (line[*column] && line[*column] == '-')
		(*column) += sign = 1;
	if ((res = parse_integer(line, column)) == -1)
		print_error("no digits", 0);
	lexeme->data_number = sign ? -res : res;
	return (lexeme);
}

t_lexeme *parse_string(const char *line, int row, int *column)
{
	unsigned start;
	t_lexeme *lexeme;

	lexeme = init_lexeme(row, (*column), STRING);
	start = ++(*column);
	while (line[*column] && line[*column] != STRING_CHAR)
		++(*column);
	if (!line[*column])
		print_error("no found close sign for string", 0);
	++(*column);
	lexeme->data_str = ft_strndup(&(line[start]), (*column) - start - 1);
	return (lexeme);
}

t_lexeme *parse_identifier(const char *line, int row, int *column,
							t_type_lexem type)
{
	unsigned start;
	t_lexeme *lexeme;

	start = *column;
	lexeme = init_lexeme(row, (*column), type);
	while (line[*column] && ft_strchr(LABEL_CHARS, line[*column]))
		++(*column);

	if (*column - start)
	{
		if (!(lexeme->data_str = ft_strndup(&(line[start]), (*column) - start)))
			print_error("error alloc memory", 0);

		if (lexeme->type == UNKNOWN)
		{
			if (line[*column] == LABEL_CHAR && ++(*column))
				lexeme->type = LABEL;
			else if (is_register(lexeme->data_str))
				lexeme->type = REGISTER;
			else
				lexeme->type = OPERATION;
		}
		else if (lexeme->type == DIRECT_LABEL || lexeme->type == INDIRECT_LABEL)
			if (!(line[*column] == LABEL_CHAR && ++(*column)))
				print_error("error label", 0);
	}
	else
		print_error("error ident", 0);
	return (lexeme);
}

t_lexeme *parse_lexeme(int row, int *column, const char *line)
{
	if (line[*column] == SEPARATOR_CHAR && ++(*column))
		return (init_lexeme(row, (*column)++, SEPARATOR));
	else if (line[*column] == CMD_CHAR && ++(*column))
		return (parse_identifier(line, row, column, COMMAND));
	else if (line[*column] == DIRECT_CHAR && ++(*column))
	{
		if (line[*column] == LABEL_CHAR && ++(*column))
			return (parse_identifier(line, row, column, DIRECT_LABEL));
		else
			return (parse_number(line, row, column, DIRECT));
	}
	else if (line[*column] == STRING_CHAR)
		return (parse_string(line, row, column));
	else if (line[*column] == LABEL_CHAR)
		return (parse_identifier(line, row, column, INDIRECT_LABEL));
	else if (ft_isdigit(line[*column]) || line[*column] == '-')
		return (parse_number(line, row, column, INDIRECT));
	else
		return (parse_identifier(line, row, column, UNKNOWN));
}
