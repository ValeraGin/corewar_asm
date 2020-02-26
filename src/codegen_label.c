/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:55:04 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 18:26:11 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"


t_label		*init_label(char *name, int op_pos)
{
	t_label	*label;

	if (!(label = (t_label *)ft_memalloc(sizeof(t_label))))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	if (!(label->name = ft_strdup(name)))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	label->op_pos = op_pos;
	label->mentions = NULL;
	label->next = NULL;
	return (label);
}

void	add_label(t_label **list, t_label *new)
{
	t_label	*c;

	if (list)
	{
		if (*list)
		{
			c = *list;
			while (c->next)
				c = c->next;
			c->next = new;
		}
		else
			*list = new;
	}
}

void	add_mention(t_mention **list, t_mention *new)
{
	t_mention	*c;

	if (list)
	{
		if (*list)
		{
			c = *list;
			while (c->next)
				c = c->next;
			c->next = new;
		}
		else
			*list = new;
	}
}

t_label	*find_label(t_label *list, char *name)
{
	t_label	*label;

	label = list;
	while (label)
	{
		if (!ft_strcmp(label->name, name))
			return (label);
		label = label->next;
	}
	return (label);
}

void	replace_mentions(t_codegen *cg)
{
	t_label		*label;
	t_mention	*mention;

	label = cg->labels;
	while (label)
	{
		if (label->op_pos == -1)
			print_error_format(GEN_ERROR,
			"label '%s' has mention, but don,t have place\n", label->name);
		else
		{
			mention = label->mentions;
			while (mention)
			{
				if (mention->size == 2)
					int32_to_b(cg->code, mention->pos,
								(int16_t)(label->op_pos - mention->op_pos),
								mention->size);
				else
					int32_to_b(cg->code, mention->pos,
						label->op_pos - mention->op_pos, mention->size);
				mention = mention->next;
			}
		}
		label = label->next;
	}
}

t_lexeme *handle_label(t_codegen *cg, t_lexeme *c)
{
	t_label	*label;

	if (!(label = find_label(cg->labels, c->data_str)))
		add_label(&(cg->labels), init_label(c->data_str, cg->oper_pos));
	if (label && label->op_pos == -1)
		label->op_pos = cg->code_pos;
	return (c->next);
}
