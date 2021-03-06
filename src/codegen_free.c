/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codegen_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:08:04 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/04 20:34:47 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen.h"

void	free_mentions(t_mention **list)
{
	t_mention	*current;
	t_mention	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void	free_labels(t_label **list)
{
	t_label	*current;
	t_label	*delete;

	current = *list;
	while (current)
	{
		delete = current;
		current = current->next;
		ft_strdel(&(delete->name));
		free_mentions(&(delete->mentions));
		ft_memdel((void **)&delete);
	}
	*list = NULL;
}

void	free_codegen(t_codegen *cg)
{
	ft_strdel(&(cg->code));
	free_labels(&(cg->labels));
}
