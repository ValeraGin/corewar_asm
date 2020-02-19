/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:09:37 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/19 18:26:23 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"

typedef struct s_assm
{
	int options;
	char *filename;
	char *out_filename;

	int input_fd;
	int output_fd;
} t_assm;

typedef struct s_position
{
	int row;
	int column;
} t_position;

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	NEW_LINE,
	END
}	t_type_lexem;

typedef struct s_lexeme
{
	struct s_lexeme *next;
	char			*content;
	t_position		position;
	t_type_lexem	type;
} t_lexeme;

typedef struct		s_champion
{
	char *name;
	char *comment;
}					t_champion;

int			handle_options(int *ac, char ***av)

#endif
