/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:52:48 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/02 23:05:43 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "decompiler.h"
#include "op.h"

#include "libft.h"

typedef struct	s_label_info
{
	int					pos_code;
	int					pos_file;
//	struct s_label_info	*next;
}				t_label_info;

typedef struct	s_men_info
{
	int					pos_code;
//	struct s__info	*next;
}				t_men_info;

t_label_info		g_label_info_tab[1000];
t_men_info			g_men_info_tab[1000];

int li = 0;
int mi = 0;

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
	if ((op->op_code == 9 || op->op_code == 12 || op->op_code == 15) && num.num16)
		g_men_info_tab[mi++].pos_code = g_label_info_tab[li-1].pos_code + num.num16;
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
			g_label_info_tab[li].pos_code = ftell(file_asm);
			g_label_info_tab[li].pos_file = ftell(file_diasm);
			li++;
			fprintf(file_diasm, "      %s ", g_op_tab[op_code].name);
			read_args(file_asm, file_diasm, &(g_op_tab[op_code]));
		}
		else
			perror_and_exit(1, "bad operation code - (%d).\n", op_code);
		fprintf(file_diasm, "\n");
	}
}

void	write_labels(FILE *file_diasm)
{
	int mi_i;
	int li_i;
	int label_c;

	label_c = 0;
	mi_i = 0;
	while (mi_i < mi)
	{
		li_i = 0;
		while (li_i < li)
		{
			if (g_label_info_tab[li_i].pos_code == g_men_info_tab[mi_i].pos_code)
			{
				fseek(file_diasm, g_label_info_tab[li_i].pos_file, SEEK_SET);
				fprintf(file_diasm, "l%d4", label_c++);
			}
			li_i++;
		}
		mi_i++;
	}
}

void	decompile_file(const char *filename, char *out_filename)
{
	FILE		*file_asm;
	FILE		*file_diasm;
	t_header	header;

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
	printf("%s[SUCCESS]%s ", PF_GREEN, PF_EOC);
	printf("Generate %s from %s\n", out_filename, filename);
	read_statement(file_asm, file_diasm);
	write_labels(file_diasm);
	fclose(file_diasm);
	fclose(file_asm);
}
