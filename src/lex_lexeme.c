/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lexeme.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:26:48 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/22 16:49:09 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "lexer.h"
#include "libft.h"
#include "error.h"
#include "lexer.h"

void add_lexeme(t_lexeme **list, t_lexeme *new)
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

t_lexeme		*init_lexeme(int row, int column, t_type_lexem type)
{
	t_lexeme	*lexeme;

	if (!(lexeme = (t_lexeme*)ft_memalloc(sizeof(t_lexeme))))
		print_error("error init_lexeme alloc memory", 0);
	lexeme->data_str = NULL;
	lexeme->data_number = 0;
	lexeme->type = type;
	lexeme->row = row;
	lexeme->column = column;
	lexeme->next = NULL;
	return (lexeme);
}
