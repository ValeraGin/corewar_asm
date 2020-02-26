/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lexeme_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:44:24 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 18:01:41 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"

t_lexeme_pos	*init_lexeme_pos(const char *filename, int fd)
{
	t_lexeme_pos	*lexeme_pos;

	if (!(lexeme_pos = (t_lexeme_pos*)ft_memalloc(sizeof(t_lexeme_pos))))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	lexeme_pos->column = 0;
	lexeme_pos->row = 0;
	lexeme_pos->filename = filename;
	lexeme_pos->fd = fd;
	return (lexeme_pos);
}
