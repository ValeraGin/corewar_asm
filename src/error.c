/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:07:42 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/27 19:35:43 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <lexer.h>

void		print_error(int ret_code, const char *str)
{
	perror(str);
	exit(ret_code);
}

void		print_error_format(int ret_code, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	exit(ret_code);
}

void		print_error_format_lex(int ret_code, t_lexeme *c,
					const char *format, ...)
{
	va_list	args;

	ft_dprintf(STDERR_FILENO,
			"%s:%d:%d: %serror%s: ",
			c->filename, c->row + 1, c->column + 1, PF_RED, PF_EOC);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	exit(ret_code);
}

void		print_error_info_pos(int ret_code, t_lexeme_pos *pos,
			const char *error_str)
{
	ft_dprintf(STDERR_FILENO,
			"%s:%d:%d: %serror%s: %s",
			pos->filename, pos->row + 1, pos->column + 1,
			PF_RED, PF_EOC, error_str);
	exit(ret_code);
}
