/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:09:37 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 21:31:13 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"

typedef struct s_assm
{
	int options;
	const char *filename;
	const char *out_filename;

	int input_fd;
	int output_fd;
}				t_assm;

typedef struct			s_label
{
	char				*name;

}						t_label;

typedef struct		s_champion
{
	char	*name;
	char	*comment;

	char	*code;
	int32_t	code_size;

}					t_champion;

int			handle_options(int *ac, const char ***av);

#endif
