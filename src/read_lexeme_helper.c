/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lexeme_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:06:13 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/24 17:59:40 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"

t_lexeme	*skip_newline(t_lexeme *c)
{
	if (c && (c->type == NEWLINE) && (c = c->next))
		return (c);
	else
		print_error("no found newline", 0);
	return (NULL);
}
