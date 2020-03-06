/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 15:57:41 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/04 19:27:40 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <lexer.h>

#include <error.h>
#include <options.h>

void		print_warning_format(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	if (g_options & (1 << ('w' - 'a')))
		ft_dprintf(STDERR_FILENO, "%s[ERROR]%s ", PF_RED, PF_EOC);
	else
		ft_dprintf(STDERR_FILENO, "%s[WARNING]%s ", PF_YELLOW, PF_EOC);
	ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	if (g_options & (1 << ('w' - 'a')))
		exit(WARN_INTO_ERR);
}

void		print_warning_format_lex(t_lexeme *c,
					const char *format, ...)
{
	va_list	args;

	if (g_options & (1 << ('w' - 'a')))
		ft_dprintf(STDERR_FILENO, "%s:%d:%d: %s[ERROR]%s ",
		c->filename, c->row + 1, c->column + 1, PF_RED, PF_EOC);
	else
		ft_dprintf(STDERR_FILENO, "%s:%d:%d: %s[WARNING]%s ",
		c->filename, c->row + 1, c->column + 1, PF_YELLOW, PF_EOC);
	va_start(args, format);
	ft_vdprintf(STDERR_FILENO, format, args);
	va_end(args);
	if (g_options & (1 << ('w' - 'a')))
		exit(WARN_INTO_ERR);
}
