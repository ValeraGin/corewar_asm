/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:27:05 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 15:02:04 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

t_op		*get_operation(char *name)
{
	size_t	i;

	i = 1;
	while (i < (sizeof(g_op_tab) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op_tab[i].name, name))
			return (&(g_op_tab[i]));
		i++;
	}
	return (NULL);
}

t_lexeme	*handle_operation(t_codegen *cg, t_lexeme *c)
{
	t_op	*op;
	int8_t	types_code;

	if ((op = get_operation(c->data_str)))
	{
		cg->code[cg->code_pos++] = op->op_code;
		c = c->next;
		if (op->args_code)
			++(cg->code_pos);
		c = handle_args(cg, c, op, &types_code);
		if (op->args_code)
			cg->code[cg->oper_pos + 1] = types_code;
		skip_newline(c);
	}
	else
		perror_fmt_lex(GEN_E, c,
			"unknown instruction '%s' found\n", c->data_str);
	return (c);
}
