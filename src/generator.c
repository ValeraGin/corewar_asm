/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:23:52 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/22 22:03:45 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "error.h"
#include "lexer.h"
#include "gen.h"


void init_champ(t_champion *ch)
{
	ch->code = 0;
	ch->code_size = 0;
	ch->comment = NULL;
	ch->name = NULL;
}

void init_codegen(t_codegen *cg)
{
	cg->code = NULL;
	cg->code_pos = 0;
	cg->code_size = 0;
	cg->labels_list = NULL;
	cg->oper_pos = 0;
}

t_lexeme	*skip_newline(t_lexeme *list)
{
	if ((list = list->next) && (list->type == NEWLINE))
		return (list);
	else
		perror("no found newline");
	return (NULL);
}

t_lexeme	*handle_header(t_lexeme *list, t_champion *ch)
{
	char **param;

	while (list && list->type == COMMAND)
	{
		param = NULL;
		if (!ft_strcmp(list->data_str,
				NAME_CMD_STRING + NAME_CMD_PREFIX_SIZE))
			param = &(ch->name);
		else if (!ft_strcmp(list->data_str,
				COMMENT_CMD_STRING + NAME_CMD_PREFIX_SIZE))
			param = &(ch->comment);
		if (param)
		{
			if ((list = list->next) && (list->type == STRING))
				*param = list->data_str;
			else
				perror("no found string after header command");
			list = skip_newline(list);
		}
		else
			perror("no found compatible command");
	}
	return (list);
}

t_op		*get_operation(char* name)
{
	size_t	i;

	i = 0;
	while (i < (sizeof(g_op_tab) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op_tab[i].name, name))
			return (&(g_op_tab[i]));
		i++;
	}
	return (NULL);
}


int8_t	handle_args(t_codegen *cg, t_lexeme *current, t_op *op)
{
	int		i;
	int8_t	types_code;

	i = 0;
	types_code = 0;
	while (i < op->count_of_args)
	{
		if (current->type & ARGUMENTS)
		{

		}
	}
	return (types_code);
}

void	handle_code(t_lexeme *list, t_champion *ch)
{
	t_op	*op;
	t_codegen cg;

	init_codegen(&cg);
	while (list->type != END)
	{
		if (list && (list->type == OPERATION))
		{
			if ((op = get_operation(list->data_str)))
			{
				cg.code[cg.code_pos++] = op->op_code;
				list = list->next;
				if (op->args_code)
					cg.code_pos++;
				// types_code = handle_args(parser, current, op);
				// if (op->args_types_code)
				// 	parser->code[parser->op_pos + 1] = types_code;
			}
			else
				perror("ddd");
		}
		else if (list && (list->type == LABEL))
		{

		}
		else perror("expected instructions or label");
	}
}


int	generator(int fd, t_lexeme *list)
{
	t_lexeme  *cur;
	t_lexeme  *last;
	t_champion ch;

	init_champ(&ch);
	cur = handle_header(list, &ch);

	handle_code(list, &ch);

	cur = list;

	return (0);
}
