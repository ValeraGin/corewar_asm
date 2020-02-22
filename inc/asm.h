/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:09:37 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/22 20:17:56 by hmathew          ###   ########.fr       */
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

int			handle_options(int *ac, const char ***av);

#endif
