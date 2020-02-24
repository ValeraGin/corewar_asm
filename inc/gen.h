/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:09:54 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/24 21:42:39 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_H
# define GEN_H

# include "libft.h"
# include "lexer.h"
# include "op.h"
# include "error.h"

typedef struct			s_mention
{
	unsigned			row;
	unsigned			column;
	int32_t				pos;
	int32_t				op_pos;
	size_t				size;
	struct s_mention	*next;
}						t_mention;

typedef struct			s_label
{
	char				*name;
	int32_t				op_pos;
	t_mention			*mentions;
	struct s_label		*next;
}						t_label;

typedef struct	s_codegen
{
	int			oper_pos;
	int			code_pos;
	t_label		*labels;
	int32_t		code_buffer_size;
	char		*code;
}				t_codegen;

// Main function for genenerate code
char*	gen_code(t_lexeme *list, int *ret_size);

t_op	*get_operation(char* name);


t_lexeme *handle_operation(t_codegen *cg, t_lexeme *c);
t_lexeme *handle_label(t_codegen *cg, t_lexeme *c);


void		handle_num(t_codegen *cg, t_lexeme *c, t_op *op);
void		handle_mention(t_codegen *cg, t_lexeme *c, t_op *op);
void		handle_register(t_codegen *cg, t_lexeme *c);

int8_t		handle_arg(t_codegen *cg, t_lexeme *c, t_op *op, int arg_i);
int8_t		get_arg_type(t_type_lexem type);
uint8_t		get_arg_code(int8_t type);



void		int32_to_b(char *data, int32_t pos, int32_t value,
								size_t size);

t_lexeme	*handle_args(t_codegen *cg, t_lexeme *c, t_op *op, int8_t *r_types);

void		add_label(t_label **list, t_label *new);
void		add_mention(t_mention **list, t_mention *new);
t_label		*init_label(char *name, int op_pos);
t_label		*find_label(t_label *list, char *name);
void		replace_mentions(t_codegen *cg);

#endif
