/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:23:52 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/25 14:59:01 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "gen.h"

void	realloc_code_buffer(t_codegen *cg)
{
	cg->code_buffer_size += CHAMP_MAX_SIZE;
	if (!(cg->code = (char *)realloc(cg->code,
			((size_t)cg->code_buffer_size + MAX_STATEMENT_SIZE))))
		print_error("Error malloc", 0);
}

void init_codegen(t_codegen *cg)
{
	cg->code = NULL;
	cg->code_pos = 0;
	cg->code_buffer_size = 0;
	cg->labels = NULL;
	cg->oper_pos = 0;
}

char*	gen_code(t_lexeme *c, int *ret_size)
{
	t_codegen cg;

	init_codegen(&cg);
	while (c->type != END)
	{
		if (cg.code_pos >= cg.code_buffer_size)
			realloc_code_buffer(&cg);
		cg.oper_pos = cg.code_pos;
		if (c && (c->type == OPERATION))
			c = handle_operation(&cg, c);
		else if (c && (c->type == LABEL))
			c = handle_label(&cg, c);
		else if (c && (c->type == NEWLINE))
			c = c->next;
		else print_error("expected instructions or label", 0);
	}
	replace_mentions(&cg);
	*ret_size = cg.code_pos;
	return(cg.code);
}
