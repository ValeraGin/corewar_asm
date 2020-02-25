/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:09:55 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/25 19:06:49 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "asm.h"
#include "error.h"

#define OFFSETOF(st, m) ((size_t)&(((st *)0)->m))

typedef struct		s_cmd
{
	char			*name;
	int				max_length;
	int				offset;
}					t_cmd;

t_cmd	g_cmd_tab[2] =
{
	{NAME_CMD_STRING, PROG_NAME_LENGTH, OFFSETOF(t_champion, name)/8},
	{COMMENT_CMD_STRING, COMMENT_LENGTH, OFFSETOF(t_champion, comment)/8}
};

t_lexeme	*read_header(t_lexeme *c, t_champion *ch)
{
	int i;
	t_cmd *cmd;

	while (c && c->type == COMMAND || c->type == NEWLINE)
	{
		if (c->type == NEWLINE && (c = c->next))
			continue;
		cmd = NULL;
		i = -1;
		while (++i < (sizeof(g_cmd_tab) / sizeof(t_cmd)) && !cmd)
			if (!ft_strcmp(c->data_str, g_cmd_tab[i].name + CMD_PREF_SIZE))
				cmd = &(g_cmd_tab[i]);
		if (!cmd)
			print_error("no found compatible command", 0);
		if (!((c = c->next) && (c->type == STRING)))
			print_error("no found string after header command", 0);
		((char **)ch)[cmd->offset] = c->data_str;
		if (ft_strlen(c->data_str) > cmd->max_length)
			print_error("length string big", 0);
		c = skip_newline(c->next);
	}
	return (c);
}
