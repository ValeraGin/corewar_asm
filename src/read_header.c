/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:09:55 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 20:09:45 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "asm.h"
#include "error.h"
#include "header.h"

t_cmd	g_cmd_tab[2] =
{
	{NAME_CMD_STRING, PROG_NAME_LENGTH,
		(((size_t)&(((t_champion *)0)->name))) / 8},
	{COMMENT_CMD_STRING, COMMENT_LENGTH,
		(((size_t)&(((t_champion *)0)->comment))) / 8}
};

t_lexeme	*read_header(t_lexeme *c, t_champion *ch)
{
	size_t	i;
	t_cmd	*cmd;

	while (c && (c->type == COMMAND || c->type == NEWLINE))
	{
		if (c->type == NEWLINE && (c = c->next))
			continue;
		cmd = NULL;
		i = -1;
		while (++i < (sizeof(g_cmd_tab) / sizeof(t_cmd)) && !cmd)
			if (!ft_strcmp(c->data_str, g_cmd_tab[i].name + CMD_PREF_SIZE))
				cmd = &(g_cmd_tab[i]);
		if (!cmd)
			print_error_format_lex(GEN_ERROR, c,
				"command %s don't exist\n", c->data_str);
		if (!((c = c->next) && (c->type == STRING)))
			print_error_format_lex(GEN_ERROR, c,
			"no found string parameter after header command %s\n", cmd->name);
		((char **)ch)[cmd->offset] = c->data_str;
		if (ft_strlen(c->data_str) > (size_t)cmd->max_length)
			print_error_format_lex(GEN_ERROR, c,
		"maximum length for %s command is %d\n", cmd->name, cmd->max_length);
		c = skip_newline(c->next);
	}
	return (c);
}
