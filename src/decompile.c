/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:52:48 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 20:51:22 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "decompiler.h"
#include "op.h"

void	perror_and_exit(int exit_code, char *format, ...)
{
	va_list	args;

	va_start(args, format);
	vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	exit(exit_code);
}

void	read_arg(FILE *file_asm, FILE *file_diasm, char arg_code, t_op *op)
{
	union u_num	num;
	int			size;
	const char	*size_str;

	num.num32 = 0;
	if (arg_code == REG_CODE)
	{
		fprintf(file_diasm, "r");
		size_str = "%hd";
		size = 1;
	}
	else if (arg_code == DIR_CODE)
	{
		fprintf(file_diasm, "%%");
		size_str = (op->short_tdir) ? "%hd" : "%d";
		size = (op->short_tdir) ? 2 : 4;
	}
	else
	{
		size_str = "%hd";
		size = 2;
	}
	while (size--)
		fread(&(num.byte[size]), sizeof(char), 1, file_asm);
	fprintf(file_diasm, size_str, num);
}

void	read_args(FILE *file_asm, FILE *file_diasm, t_op *op)
{
	char	arg_types;
	int		arg_i;

	if (op->args_code)
	{
		if (!(fread(&arg_types, sizeof(char), 1, file_asm) == 1))
			perror_and_exit(1, "not expected end of file");
	}
	else
		arg_types = op->arg_type[0] << 6;
	arg_i = 0;
	while (arg_i < op->count_of_args)
	{
		read_arg(file_asm, file_diasm,
			(arg_types & 3 << (6 - (arg_i * 2))) >> (6 - (arg_i * 2)), op);
		arg_i++;
		if (arg_i != op->count_of_args)
			fprintf(file_diasm, ", ");
	}
}

void	read_statement(FILE *file_asm, FILE *file_diasm)
{
	unsigned char	op_code;

	while (fread(&op_code, sizeof(char), 1, file_asm) == 1)
	{
		if (op_code && op_code < (sizeof(g_op_tab) / sizeof(t_op)))
		{
			fprintf(file_diasm, "\t%s ", g_op_tab[op_code].name);
			read_args(file_asm, file_diasm, &(g_op_tab[op_code]));
		}
		else
			perror_and_exit(1, "bad operation code - (%d).\n", op_code);
		fprintf(file_diasm, "\n");
	}
}

void	decompile_file(int options, const char *filename, char *out_filename)
{
	FILE		*file_asm;
	FILE		*file_diasm;
	t_header	header;

	(void)options;
	file_asm = fopen(filename, "r");
	if (file_asm == NULL)
		perror_and_exit(1, "Error to open the file %s\n", filename);
	if (fread(&header, sizeof(t_header), 1, file_asm) != 1)
		perror_and_exit(1, "Error to read header %s\n", filename);
	file_diasm = fopen(out_filename, "w");
	if (file_diasm == NULL)
		perror_and_exit(1, "Error to open the file for writing %s\n", filename);
	fprintf(file_diasm, "%s \"%s\"\n%s \"%s\"\n\n",
		NAME_CMD_STRING, header.prog_name, COMMENT_CMD_STRING, header.comment);
	read_statement(file_asm, file_diasm);
	fclose(file_diasm);
	fclose(file_asm);
}
