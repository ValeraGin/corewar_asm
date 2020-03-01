/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_parse_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:46:55 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 15:40:04 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include "error.h"
#include "lexer.h"

void		handle_multiline(t_lexeme *lexeme, t_lexeme_pos *pos, char **line)
{
	char	*tmp;

	while (get_next_line(pos->fd, line) == GNL_OK)
	{
		pos->row++;
		pos->column = 0;
		while ((*line)[pos->column] && (*line)[pos->column] != STRING_CHAR)
			++(pos->column);
		if (!(tmp = ft_strndup(*line, pos->column)))
			print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
		if (!(lexeme->data_str = ft_strjoin_wf(lexeme->data_str, tmp, 2)))
			print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
		if ((*line)[pos->column] == STRING_CHAR)
			return ;
		if (!(lexeme->data_str = ft_strjoinc_wf(lexeme->data_str, '\n', 0, 1)))
			print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
		ft_strdel(line);
	}
	print_error_info_pos(LEX_ERROR, pos, " No found close sign for string\n");
}

t_lexeme	*parse_string(char **line, t_lexeme_pos *pos)
{
	unsigned	start;
	t_lexeme	*lexeme;

	lexeme = init_lexeme(pos, STRING);
	start = ++(pos->column);
	while ((*line)[pos->column] && (*line)[pos->column] != STRING_CHAR)
		++(pos->column);
	if (!(lexeme->data_str = ft_strndup(&((*line)[start]),
										pos->column - start)))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	if (!(*line)[pos->column])
	{
		if (!(lexeme->data_str = ft_strjoinc_wf(lexeme->data_str, '\n', 0, 1)))
			print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
		ft_strdel(line);
		handle_multiline(lexeme, pos, line);
	}
	++(pos->column);
	return (lexeme);
}
