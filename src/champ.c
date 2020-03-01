/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:02:07 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 14:09:14 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error.h"
#include "gen.h"

void	free_champ(t_champion *ch)
{

	ft_strdel(&(ch->code));
	ft_strdel(&(ch->name));
	ft_strdel(&(ch->comment));
}

void	init_champ(t_champion *ch)
{
	ch->code = 0;
	ch->code_size = 0;
	ch->comment = NULL;
	ch->name = NULL;
}

void	champ_write_to_file(t_champion *ch, int fd)
{
	int32_t	len;
	int32_t	pos;
	char	*header;

	pos = 0;
	len = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	if (!(header = ft_strnew((size_t)len)))
		print_error(ALLOC_ERROR, ALLOC_ERROR_STRING);
	int32_to_b(header, pos, COREWAR_EXEC_MAGIC, 4);
	pos += 4;
	if (ch->name)
		ft_memcpy(&header[pos], ch->name, ft_strlen(ch->name));
	pos += PROG_NAME_LENGTH;
	pos += 4;
	int32_to_b(header, pos, ch->code_size, 4);
	pos += 4;
	if (ch->comment)
		ft_memcpy(&header[pos], ch->comment, ft_strlen(ch->comment));
	write(fd, header, (size_t)len);
	free(header);
	write(fd, ch->code, ch->code_size);
}
