/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_arg_men.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:15:51 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 14:58:37 by hmathew          ###   ########.fr       */
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

	size = (c->type == DIRECT_LABEL && !op->short_tdir) ?
				DIR_SIZE : IND_SIZE;
	if (!(label = find_label(cg->labels, c->data_str)))
	{
		label = init_label(c->data_str, -1);
		add_label(&(cg->labels), label);
	}
	add_mention(&label->mentions, init_mention(cg, c, size));
	cg->code_pos += size;
}

void		replace_mentions(t_codegen *cg)
{
	t_label		*label;
	t_mention	*mention;

	label = cg->labels;
	while (label)
	{
		if (label->op_pos == -1)
			print_error_format(GEN_E,
			"label '%s' has mention, but don,t have place\n", label->name);
		else
		{
			mention = label->mentions;
			while (mention)
			{
				if (mention->size == 2)
					int32_to_b(cg->code, mention->pos,
					(int16_t)(label->op_pos - mention->op_pos), mention->size);
				else
					int32_to_b(cg->code, mention->pos,
						label->op_pos - mention->op_pos, mention->size);
				mention = mention->next;
			}
		}
		label = label->next;
	}
}
