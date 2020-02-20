/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:21:56 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 14:35:49 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum
{
	COMMAND,
	STRING,
	LABEL,
	OPERATOR,
	REGISTER,
	DIRECT,
	DIRECT_LABEL,
	INDIRECT,
	INDIRECT_LABEL,
	SEPARATOR,
	END
}	t_type_lexem;

typedef struct s_lexeme
{
	struct s_lexeme *next;
	char			*content;
	int row;
	int column;
	t_type_lexem	type;
} t_lexeme;

t_lexeme	*parse_lexeme(int row, int *column, const char *line);

t_lexeme	*read_lexems(int fd);

#endif
