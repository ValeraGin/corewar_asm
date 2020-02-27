/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:03:55 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 19:34:28 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_lexeme_list(t_lexeme **list)
{
	t_lexeme	*current;
	t_lexeme	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}
