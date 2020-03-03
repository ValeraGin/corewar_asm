/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:52:48 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/03 22:38:35 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "error.h"

#include "decompiler.h"
#include "op.h"

#include "libft.h"

void	fprintf_pos(FILE *file, int pos, char *format, ...)
{
	va_list	args;

	va_start(args, format);
	fseek(file, pos, SEEK_SET);
	vfprintf(file, format, args);
	va_end(args);
}

void	read_statement(t_decompiler *dec)
{
	unsigned char	op_code;
	t_label_info	li;

	while (fread(&op_code, sizeof(char), 1, dec->file_asm) == 1)
	{
		if (op_code && op_code < (sizeof(g_op_tab) / sizeof(t_op)))
		{
			li.name = 0;
			li.pos_code = ftell(dec->file_asm);
			li.pos_file = ftell(dec->file_diasm);
			ft_lstadd(&(dec->labels), ft_lstnew(&li, sizeof(li)));
			fprintf(dec->file_diasm, "       %s ", g_op_tab[op_code].name);
			read_args(dec, &(g_op_tab[op_code]));
		}
		else
			perror_format(1, "bad operation code - (%d).\n", op_code);
		fprintf(dec->file_diasm, "\n");
	}
}

void	write_labels(t_decompiler *dec)
{
	t_list			*label_curr;
	t_list			*men_curr;
	t_label_info	*li;
	t_men_info		*mi;
	int				label_c;

	label_c = 0;
	label_curr = dec->labels;
	while (label_curr)
	{
		li = (t_label_info*)label_curr->content;
		men_curr = dec->mentions;
		while (men_curr && (mi = (t_men_info*)men_curr->content))
		{
			if (mi->pos_code == li->pos_code)
			{
				if (!li->name)
					fprintf_pos(dec->file_diasm, li->pos_file,
						"l%03d:", (li->name = ++label_c));
				fprintf_pos(dec->file_diasm, mi->pos_file, ":l%03d", li->name);
			}
			men_curr = men_curr->next;
		}
		label_curr = label_curr->next;
	}
}

void	decompile_file(const char *filename, char *out_filename)
{
	t_decompiler	decompiler;
	t_header		header;

	decompiler.labels = 0;
	decompiler.mentions = 0;
	if (!(decompiler.file_asm = fopen(filename, "r")))
		perror_format(1, "Error to open the file %s\n", filename);
	if (fread(&header, sizeof(t_header), 1, decompiler.file_asm) != 1)
		perror_format(1, "Error to read header %s\n", filename);
	if ((decompiler.file_diasm = fopen(out_filename, "w")) == NULL)
		perror_format(1, "Error to open the file for writing %s\n", filename);
	fprintf(decompiler.file_diasm, "%s \"%s\"\n%s \"%s\"\n\n",
		NAME_CMD_STRING, header.prog_name, COMMENT_CMD_STRING, header.comment);
	read_statement(&decompiler);
	ft_lstrev(&(decompiler.labels));
	ft_lstrev(&(decompiler.mentions));
	write_labels(&decompiler);
	printf("%s[SUCCESS]%s Generate %s from %s\n",
			PF_GREEN, PF_EOC, out_filename, filename);
	ft_lstdel(&(decompiler.labels), &ft_lstdel_func);
	ft_lstdel(&(decompiler.mentions), &ft_lstdel_func);
	fclose(decompiler.file_diasm);
	fclose(decompiler.file_asm);
	ft_strdel(&out_filename);
}
