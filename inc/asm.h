/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:09:37 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 20:31:32 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "lexer.h"

typedef struct s_assm
{
	int options;
	const char *filename;
	char *out_filename;
	int input_fd;
	int output_fd;
}				t_assm;

typedef struct		s_champion_
{
	char	*name;
	char	*comment;
	int32_t	code_size;
	char	*code;
}					t_champion;


void		free_champ(t_champion *ch);
void		init_champ(t_champion *ch);
void		champ_write_to_file(t_champion *ch, int fd);

t_lexeme	*read_header(t_lexeme *c, t_champion *ch);
char*		gen_code(t_lexeme *list, int *ret_size);

int			handle_option_str(const char *option_str);

#endif
