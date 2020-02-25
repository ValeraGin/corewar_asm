/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:03:42 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/25 20:29:30 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <sysexits.h>

#include "libft.h"
#include "asm.h"
#include "lexer.h"
#include "error.h"
#include "gen.h"

static void	print_usage(void)
{
	ft_printf("Usage: ./asm [-a] [*] <champion.s>\n");
	exit(0);
}

void	free_assm(t_assm *assm)
{
	ft_strdel(&(assm->out_filename));
}

int			compile_file(int options, const char *filename, char *out_filename)
{
	t_assm		assm;
	t_lexeme	*lexems;
	t_lexeme	*lexems_head;
	t_champion	ch;


	assm.options = options;
	assm.filename = filename;
	assm.out_filename = out_filename;
	if ((assm.input_fd = open(assm.filename, O_RDONLY)) < 0)
		print_error("Can't read source file", errno);
	if ((assm.output_fd = open(assm.out_filename, O_CREAT | O_RDWR, 0644)) < 0)
		print_error("Can't open to write file", errno);
	lexems = lexems_head = read_lexems(assm.input_fd);
	init_champ(&ch);
	lexems = read_header(lexems, &ch);
	ch.code = gen_code(lexems, &(ch.code_size));
	free_lexeme_list(&(lexems_head));
	if (!champ_write_to_file(&ch, assm.output_fd))
		print_error("Error when write already generated champ code to file", errno);
	free_champ(&ch);
	free_assm(&assm);
	return (1);
}

int		main(int argc, char const *argv[])
{
	int			options;
	int			i;

	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	if (!(options = handle_options(&argc, &argv)))
		return (0);
	i = 1;
	while (i < argc)
	{
		compile_file(options, argv[i], replace_file_ext(argv[i], ".cor"));
		i++;
	}
	return (0);
}
