/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:09:54 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/22 20:45:32 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_H
# define GEN_H

# include "lexer.h"

typedef struct		s_champion_
{
	char	*name;
	char	*comment;
	int32_t	code_size;
	char	*code;
}					t_champion;

typedef struct			s_label
{
	char				*name;
	void				*pointers;
	void				*codeops;
	struct s_label		*next;
}						t_label;

typedef struct	s_codegen
{
	int			oper_pos;
	int			code_pos;
	t_label		*labels_list;
	int32_t		code_size;
	char		*code;
}				t_codegen;

int		generator(int fd, t_lexeme *list);

#endif
