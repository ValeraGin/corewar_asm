/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompiler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:53:24 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 20:53:39 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECOMPILER_H
# define DECOMPILER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "op.h"

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

void				decompile_file(int options, const char *filename,
										char *out_filename);

#endif
