/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompiler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:53:24 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/04 21:17:34 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECOMPILER_H
# define DECOMPILER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "op.h"

# include "libft.h"

typedef struct		s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

union				u_num
{
	int8_t	byte[4];
	int16_t	num16;
	int32_t	num32;
};

typedef struct		s_label_info
{
	int					pos_code;
	int					pos_file;
	int					name;
}					t_label_info;

typedef struct		s_men_info
{
	int					pos_code;
	int					pos_file;
}					t_men_info;

typedef struct		s_decompiler
{
	FILE	*file_asm;
	FILE	*file_diasm;
	t_list	*labels;
	t_list	*mentions;
}					t_decompiler;

void				del_label(void *li, size_t s);
void				del_mention(void *mi, size_t s);

t_label_info		*init_label_i(int pos_code, int pos_file);
t_men_info			*init_mention_info(int pos_code, int pos_file);

void				fprintf_pos(FILE *file, int pos, char *format, ...);

void				decompile_file(const char *filename, char *out_filename);
void				read_args(t_decompiler *decompiler, t_op *op);

#endif
