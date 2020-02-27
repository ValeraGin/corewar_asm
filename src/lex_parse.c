/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:24:20 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 20:01:31 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include "error.h"
#include "lexer.h"

int			parse_integer(const char *str, int *i)
{
	long	nbr;
	long	nbrtemp;

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

t_lexeme	*parse_number(const char *line, t_lexeme_pos *pos,
					t_type_lexem type)
{
	unsigned	start;
	t_lexeme	*lexeme;
	int			sign;
	int			res;

	lexeme = init_lexeme(pos, type);
	start = pos->column;
	sign = 0;
	if (line[pos->column] && line[pos->column] == '-')
		pos->column += sign = 1;
	if ((res = parse_integer(line, &(pos->column))) == -1)
		print_error_info_pos(LEX_ERROR, pos, "expected a number\n");
	lexeme->data_number = sign ? -res : res;
	return (lexeme);
}

t_lexeme	*parse_identifier(char *line, t_lexeme_pos *pos,
	t_type_lexem type)
{
	int			start;
	t_lexeme	*lexeme;

	start = pos->column;
	lexeme = init_lexeme(pos, type);
	while (line[pos->column] && ft_strchr(LABEL_CHARS, line[pos->column]))
		++(pos->column);
	if (!(pos->column - start))
		print_error_info_pos(LEX_ERROR, pos, "wrong identification\n");
	if (!(lexeme->data_str = ft_strndup(&(line[start]), pos->column - start)))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	if (lexeme->type == UNKNOWN)
	{
		if (line[pos->column] == LABEL_CHAR && ++(pos->column))
			lexeme->type = LABEL;
		else if (is_register(lexeme->data_str) && (start = 1))
		{
			lexeme->type = REGISTER;
			lexeme->data_number = parse_integer(lexeme->data_str, &start);
			free(lexeme->data_str);
		}
		else
			lexeme->type = OPERATION;
	}
	return (lexeme);
}

t_lexeme	*parse_lexeme(char **line, t_lexeme_pos *pos)
{
	if ((*line)[pos->column] == SEPARATOR_CHAR && ++(pos->column))
		return (init_lexeme(pos, SEPARATOR));
	else if ((*line)[pos->column] == CMD_CHAR && ++(pos->column))
		return (parse_identifier((*line), pos, COMMAND));
	else if ((*line)[pos->column] == DIRECT_CHAR && ++(pos->column))
	{
		if ((*line)[pos->column] == LABEL_CHAR && ++(pos->column))
			return (parse_identifier((*line), pos, DIRECT_LABEL));
		else
			return (parse_number((*line), pos, DIRECT));
	}
	else if ((*line)[pos->column] == STRING_CHAR)
		return (parse_string(line, pos));
	else if ((*line)[pos->column] == LABEL_CHAR && ++(pos->column))
		return (parse_identifier((*line), pos, INDIRECT_LABEL));
	else if (ft_isdigit((*line)[pos->column]) || (*line)[pos->column] == '-')
		return (parse_number((*line), pos, INDIRECT));
	else
		return (parse_identifier((*line), pos, UNKNOWN));
}
