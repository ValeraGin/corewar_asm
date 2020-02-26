/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lexeme_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:06:13 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 18:27:33 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "error.h"

t_lexeme	*skip_newline(t_lexeme *c)
{
	if (c && (c->type == NEWLINE) && (c = c->next))
		return (c);
	else
		print_error_format_lex(GEN_ERROR, c, "expected newline\n");
	return (NULL);
}
