/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lexeme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:26:48 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 19:34:41 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"
#include "libft.h"
#include "error.h"

void		add_lexeme(t_lexeme **list, t_lexeme *new)
{
	t_lexeme	*current;

	if (list)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

t_lexeme	*init_lexeme(t_lexeme_pos *pos, t_type_lexem type)
{
	t_lexeme	*lexeme;

	if (!(lexeme = (t_lexeme*)ft_memalloc(sizeof(t_lexeme))))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	lexeme->data_str = NULL;
	lexeme->data_number = 0;
	lexeme->type = type;
	lexeme->row = pos->row;
	lexeme->column = pos->column;
	lexeme->filename = pos->filename;
	lexeme->next = NULL;
	return (lexeme);
}
