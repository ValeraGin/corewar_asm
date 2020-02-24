/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_arg_reg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:17:27 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/24 21:40:01 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

void		handle_register(t_codegen *cg, t_lexeme *c)
{
	int32_to_b(cg->code, cg->code_pos, (int8_t)c->data_number, 1);
	cg->code_pos += 1;
}
