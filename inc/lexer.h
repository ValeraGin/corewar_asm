/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:21:56 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/25 16:24:31 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "op.h"
# include "libft.h"

# define ARGUMENTS 1 << 16

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

typedef struct s_lexeme
{
	struct s_lexeme *next;
	char		*data_str;
	int			data_number;
	int row;
	int column;
	t_type_lexem	type;
} t_lexeme;

t_lexeme	*skip_newline(t_lexeme *c);

int			is_register(const char *str);
int			is_delimiter(char c);
int			is_whitespace(char c);

int			skip_whitespaces(int *column, const char *line);
int			skip_comment(int *column, const char *line);

t_lexeme	*init_lexeme(int row, int column, t_type_lexem type);
void		add_lexeme(t_lexeme **list, t_lexeme *new);

t_lexeme	*parse_lexeme(int row, int *column, const char *line);

t_lexeme	*read_lexems(int fd);

#endif
