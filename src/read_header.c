/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:09:55 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 16:22:51 by hmathew          ###   ########.fr       */
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

#define CMD_NOT_EXIST	"command %s don't exist\n"
#define NO_STR_AF_CMD	"no found string parameter after header command %s\n"
#define CMD_IS_SET		"command %s is already set\n"
#define LIMIT_STRLEN	"maximum length for %s command is %d\n"

t_lexeme	*read_header(t_lexeme *c, t_champion *ch)
{
	size_t	i;
	t_cmd	*cmd;

	while (c && (c->type == COMMAND || c->type == NEWLINE))
	{
		if (c->type == NEWLINE)
			c = skip_newline(c);
		cmd = NULL;
		i = -1;
		while (++i < (sizeof(g_cmd_tab) / sizeof(t_cmd)) && !cmd)
			if (!ft_strcmp(c->data_str, g_cmd_tab[i].name + CMD_PREF_SIZE))
				cmd = &(g_cmd_tab[i]);
		if (!cmd)
			perror_fmt_lex(GEN_E, c, CMD_NOT_EXIST, c->data_str);
		if (!((c = c->next) && (c->type == STRING)))
			perror_fmt_lex(GEN_E, c, NO_STR_AF_CMD, cmd->name);
		if (((char **)ch)[cmd->offset])
			perror_fmt_lex(GEN_E, c, CMD_IS_SET, cmd->name);
		else
			((char **)ch)[cmd->offset]= c->data_str;
		if (ft_strlen(c->data_str) > (size_t)cmd->max_length)
			perror_fmt_lex(GEN_E, c, LIMIT_STRLEN, cmd->name, cmd->max_length);
		c = skip_newline(c->next);
	}
	return (c);
}
