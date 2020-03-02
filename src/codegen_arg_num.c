/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_arg_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:15:09 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/02 21:10:38 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

void		handle_num(t_codegen *cg, t_lexeme *c, t_op *op)
{
	size_t		size;

	size = (c->type == DIRECT && !op->short_tdir) ? DIR_SIZE : IND_SIZE;
	if (size == 2)
		int32_to_b(cg->code, cg->code_pos, (int16_t)c->data_number, size);
	else
		int32_to_b(cg->code, cg->code_pos, c->data_number, size);
	cg->code_pos += size;
}
