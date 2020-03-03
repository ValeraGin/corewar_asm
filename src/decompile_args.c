/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:42:09 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/03 22:36:03 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "decompiler.h"

const char	*arg_formatstr_size(t_decompiler *decompiler,
					char arg_code, int *size, t_op *op)
{
	const char *size_str;

	if (arg_code == REG_CODE)
	{
		fprintf(decompiler->file_diasm, "r");
		size_str = "%hd";
		*size = 1;
	}
	else if (arg_code == DIR_CODE)
	{
		fprintf(decompiler->file_diasm, "%%");
		size_str = (op->short_tdir) ? "%hd" : "%d";
		*size = (op->short_tdir) ? 2 : 4;
	}
	else
	{
		size_str = "%hd";
		*size = 2;
	}
	return (size_str);
}

void		read_arg(t_decompiler *dec, char arg_code, t_op *op)
{
	union u_num	num;
	int			size;
	const char	*size_str;
	t_men_info	mi;

	num.num32 = 0;
	size_str = arg_formatstr_size(dec, arg_code, &size, op);
	while (size--)
		fread(&(num.byte[size]), sizeof(char), 1, dec->file_asm);
	if ((op->op_code == 9 || op->op_code == 12 || op->op_code == 15)
				&& num.num16)
	{
		mi.pos_code = ((t_label_info*)dec->labels->content)->pos_code
				+ num.num16;
		mi.pos_file = ftell(dec->file_diasm);
		ft_lstadd(&(dec->mentions), ft_lstnew(&mi, sizeof(mi)));
		fprintf(dec->file_diasm, "%05hd", num.num16);
	}
	else
		fprintf(dec->file_diasm, size_str, num);
}

void		read_args(t_decompiler *decompiler, t_op *op)
{
	char	arg_types;
	int		arg_i;

	if (op->args_code)
	{
		if (!(fread(&arg_types, sizeof(char), 1, decompiler->file_asm) == 1))
			perror_format(1, "not expected end of file");
	}
	else
		arg_types = op->arg_type[0] << 6;
	arg_i = 0;
	while (arg_i < op->count_of_args)
	{
		read_arg(decompiler,
			(arg_types & 3 << (6 - (arg_i * 2))) >> (6 - (arg_i * 2)), op);
		arg_i++;
		if (arg_i != op->count_of_args)
			fprintf(decompiler->file_diasm, ", ");
	}
}
