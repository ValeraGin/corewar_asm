/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:21:56 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 20:07:48 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	INSTRUCTION,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	END,
	NEWLINE,
	UNKNOWN
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

int			is_register(const char *str);
int			is_delimiter(char c);
int			is_whitespace(char c);

void		skip_whitespaces(int *column, const char *line);
void		skip_comment(int *column, const char *line);

t_lexeme	*init_lexeme(int row, int column, t_type_lexem type);
void		add_lexeme(t_lexeme **list, t_lexeme *new);

t_lexeme	*parse_lexeme(int row, int *column, const char *line);

t_lexeme	*read_lexems(int fd);

#endif
