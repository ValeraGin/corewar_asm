/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:21:56 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 20:48:52 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "op.h"
# include "libft.h"

# define ARGUMENTS 1 << 16

/*
**	types lexemes
*/
typedef enum
{
	COMMAND = 0,
	STRING = 1,
	LABEL = 2,
	OPERATION = 3,
	REGISTER = 4 | ARGUMENTS,
	DIRECT = 5 | ARGUMENTS,
	DIRECT_LABEL = 6 | ARGUMENTS,
	INDIRECT = 7 | ARGUMENTS,
	INDIRECT_LABEL = 8 | ARGUMENTS,
	SEPARATOR = 9,
	END = 10,
	NEWLINE = 11,
	UNKNOWN = 12
}	t_type_lexem;

/*
**	lexeme position in file
*/
typedef struct	s_lexeme_pos
{
	const char	*filename;
	int			fd;
	int			row;
	int			column;
}				t_lexeme_pos;

t_lexeme_pos	*init_lexeme_pos(const char *filename, int	fd);

typedef struct	s_lexeme
{
	struct s_lexeme *next;
	char			*data_str;
	int				data_number;
	const char		*filename;
	int				row;
	int				column;
	t_type_lexem	type;
}				t_lexeme;

t_lexeme		*init_lexeme(t_lexeme_pos *pos, t_type_lexem type);
void			add_lexeme(t_lexeme **list, t_lexeme *new);
void			free_lexeme_list(t_lexeme **list);

/*
**	register is "r[0-9]{1,2}/n"
**	example: r01, r5
**	exception: r00, r0 - not a register
*/
int				is_register(const char *str);

int				is_delimiter(char c);
int				is_whitespace(char c);

/*
**	skip_whitespaces('\t', '\v', '\f', '\r', ' ')
*/
int				skip_whitespaces(char *line, t_lexeme_pos *pos);

/*
**	skip_comment
**	skip all chars after comment_char ('#' || ';')
**	to the end of the line
*/
int				skip_comment(char *line, t_lexeme_pos *pos);

/*
**	skip function for codegen/header reader
*/
t_lexeme		*skip_newline(t_lexeme *c);

t_lexeme		*parse_string(char **line, t_lexeme_pos *pos);
t_lexeme		*parse_lexeme(char **line, t_lexeme_pos *pos);
t_lexeme		*read_lexems(int fd, const char *filename);

#endif
