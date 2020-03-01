/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_arg_reg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:17:27 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 16:28:46 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"
#include "error.h"

void		handle_register(t_codegen *cg, t_lexeme *c)
{
	if (c->data_number == 0)
		print_warning_format_lex(c, "Register value has null value\n");
	if (c->data_number > REG_NUMBER)
		print_warning_format_lex(c, "Register index (%d) bigger than max - (%d)\n",
			c->data_number, REG_NUMBER);
	int32_to_b(cg->code, cg->code_pos, (int8_t)c->data_number, 1);
	cg->code_pos += 1;
}
