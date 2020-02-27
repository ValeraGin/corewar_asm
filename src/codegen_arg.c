/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:07:19 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 19:34:05 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

uint8_t	get_arg_code(int8_t type)
{
	if (type == T_DIR)
		return (DIR_CODE);
	else if (type == T_REG)
		return (REG_CODE);
	else
		return (IND_CODE);
}

int8_t	get_arg_type(t_type_lexem type)
{
	if (type == DIRECT || type == DIRECT_LABEL)
		return (T_DIR);
	else if (type == INDIRECT || type == INDIRECT_LABEL)
		return (T_IND);
	else if (type == REGISTER)
		return (T_REG);
	else
		return (0);
}

int8_t	handle_arg(t_codegen *cg, t_lexeme *c, t_op *op, int arg_i)
{
	int8_t	type;

	type = get_arg_type(c->type);
	if (!(op->arg_type[arg_i] & type))
		print_error_format_lex(GEN_ERROR, c, "wrong type of parameter\n");
	if (c->type == INDIRECT_LABEL
		|| c->type == DIRECT_LABEL)
		handle_mention(cg, c, op);
	else if (c->type == INDIRECT
		|| c->type == DIRECT)
		handle_num(cg, c, op);
	else
		handle_register(cg, c);
	return (type);
}
