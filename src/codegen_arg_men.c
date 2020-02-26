/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_arg_men.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:15:51 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 18:21:32 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

t_mention	*init_mention(t_codegen *cg, t_lexeme *c, size_t size)
{
	t_mention	*mention;

	if (!(mention = (t_mention *)ft_memalloc(sizeof(t_mention))))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	mention->row = c->row;
	mention->column = c->column;
	mention->pos = cg->code_pos;
	mention->op_pos = cg->oper_pos;
	mention->size = size;
	mention->next = NULL;
	return (mention);
}

void		handle_mention(t_codegen *cg, t_lexeme *c, t_op *op)
{
	t_label		*label;
	size_t		size;

	size = (c->type == DIRECT_LABEL && !op->short_tdir) ? DIR_SIZE : IND_SIZE;
	if (!(label = find_label(cg->labels, c->data_str)))
	{
		label = init_label(c->data_str, -1);
		add_label(&(cg->labels), label);
	}
	add_mention(&label->mentions, init_mention(cg, c, size));
	cg->code_pos += size;
}
