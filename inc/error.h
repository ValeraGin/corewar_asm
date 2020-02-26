/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 14:08:42 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 18:25:27 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "lexer.h"

#define LEX_ERROR -50
#define GEN_ERROR -100
#define ALLOC_ERROR -100

#define ALLOC_ERROR_STRING "malloc return NULL, we can't continue work\n"

void		print_error(int ret_code, const char *str);

void		print_error_info_pos(int ret_code, t_lexeme_pos *pos,
			const char *error_str);

void		print_error_format(int ret_code, const char *format, ...);

void		print_error_format_lex(int ret_code, t_lexeme *c,
					const char *format, ...);

#endif


