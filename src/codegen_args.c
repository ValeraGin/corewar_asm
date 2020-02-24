/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 14:08:28 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/24 21:39:36 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

t_lexeme *handle_args(t_codegen *cg, t_lexeme *c, t_op *op, int8_t *r_types)
{
	int		arg_i;
	int8_t	type_arg;

	arg_i = 0;
	*r_types = 0;
	while (arg_i < op->count_of_args)
	{
		if (c->type & ARGUMENTS)
		{
			type_arg = handle_arg(cg, c, op, arg_i);
			*r_types |= (get_arg_code(type_arg) << 2 * (4 - arg_i - 1));
			c = c->next;
		}
		else
			print_error("expected argument", 0);

		if (arg_i != op->count_of_args - 1)
		{
			if (c->type != SEPARATOR)
				print_error("expected separator", 0);
			c = c->next;
		}
		arg_i++;
	}
	return (c);
}
