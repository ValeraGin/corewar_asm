/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:56:41 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/19 23:17:40 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"

int		is_whitespace(char c)
{
	return (c == '\t' ||
			c == '\v' ||
			c == '\f' ||
			c == '\r' ||
			c == ' ');
}

int	is_delimiter(char c)
{
	return (c == '\0'
			|| c == '\n'
			|| is_whitespace(c)
			|| c == CMD_CHAR
			|| c == '\"'
			|| c == DIRECT_CHAR
			|| c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR
			|| c == ALT_COMMENT_CHAR);
}


void	skip_whitespaces(int *column, const char *line)
{
	while (is_whitespace(line[*column]))
		(*column)++;
}

void	skip_comment(int *column, const char *line)
{
	if (line[*column] == COMMENT_CHAR
		|| line[*column] == ALT_COMMENT_CHAR)
		while (line[*column] && line[*column] != '\n')
			(*column)++;
}

void add_lexeme(t_lexeme **list, t_lexeme *new)
{
	t_lexeme	*current;

	if (list)
	{
		if (*list)
		{
			current = *list;
			while (current->next)
				current = current->next;
			current->next = new;
		}
		else
			*list = new;
	}
}

t_lexeme		*init_lexeme(int row, int column, t_type_lexem type)
{
	t_lexeme	*lexeme;

	if (!(lexeme = (t_lexeme*)ft_memalloc(sizeof(t_lexeme))))
		print_error("error init_lexeme alloc memory");
	lexeme->content = NULL;
	lexeme->type = type;
	lexeme->row = row;
	lexeme->column = column;
	lexeme->next = NULL;
	return (lexeme);
}

t_lexeme *parse_identifier(const char *line, int row, int *column, t_type_lexem type)
{
	unsigned start;
	t_lexeme *lexeme;

	start = *column;
	lexeme = init_lexeme(row, (*column)++, type);
	while (line[*column] && ft_strchr(LABEL_CHARS, line[*column]))
		(*column)++;
	if ((*column - start) && line[*column] == LABEL_CHAR && (*column)++)
	{
		lexeme->type = LABEL;
		lexeme->content = ft_strndup(&(line[start]), (*column) - start - 1);
		if (!lexeme->content)
			print_error("error alloc memory");
	}
	else if (((*column) - start) && is_delimiter(line[*column]))
	{
		lexeme->content = ft_strndup(&(line[start]), (*column) - start - 1);
		if (!lexeme->content)
			print_error("error alloc memory");
		if (lexeme->type == INDIRECT)
			lexeme->type = (is_register(lexeme->content)) ? REGISTER : OPERATOR;
	}
	else
		print_error("error lex");
}

t_lexeme *parse_lexeme(t_lexeme **list, int row, int *column, const char *line)
{
	if (line[*column] == SEPARATOR_CHAR && (*column)++)
		return (init_lexeme(row, (*column)++, SEPARATOR));
	else if (line[*column] == CMD_CHAR && (*column)++)
		return (parse_identifier(line, row, *column, COMMAND));
	else if (line[*column] == DIRECT_CHAR && (*column)++)
	{
		if (line[*column] == LABEL_CHAR && (*column)++)
			return (parse_identifier(line, row, *column, DIRECT_LABEL));
		else
			return (parse_number(line, row, *column, DIRECT));
	}
	else if (line[*column] == STRING_CHAR)
		return (parse_string(line, row, *column, STRING));
	else if (line[*column] == LABEL_CHAR)
		return (parse_identifier(line, row, *column, INDIRECT_LABEL));
	else
		return (parse_number(line, row, *column, INDIRECT));
}

t_lexeme	*read_lexems(int fd)
{
	t_lexeme	*list;
	char		*line;
	int			row;
	int			column;
	
	row = 0;
	while (get_next_line(fd, &line) == GNL_OK)
	{
		column = 0;
		skip_whitespaces(&column, line);
		skip_comment(&column, line);
		if (line[column])
			parse_lexem(&column, line);

		row++;
	}
}