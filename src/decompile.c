/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:52:48 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 22:19:45 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompiler.h"

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;

int		decompile_file(int options, const char *filename, char *out_filename)
{
	FILE *file_asm;
	FILE *file_diasm;
	header_t header;

	file_asm = fopen(filename, "r");
	file_diasm = fopen(out_filename, "w");

	if (file_diasm == NULL)
	{
		fprintf(stderr, "Error to open the file for writing %s\n", filename);
		exit(1);
	}
	if (file_asm == NULL)
	{
		fprintf(stderr, "Error to open the file %s\n", filename);
		exit(1);
	}
	if (fread(&header, sizeof(header_t), 1, file_asm) == sizeof(header_t))
	{
		fprintf(stderr, "Error to read header %s\n", filename);
		exit(1);
	}
	fprintf(file_diasm, "%s \"%s\"\n%s \"%s\"",
	NAME_CMD_STRING, header.prog_name,
	COMMENT_CMD_STRING, header.comment);
	fclose(file_diasm);
	fclose(file_asm);
}
