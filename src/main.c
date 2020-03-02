/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:03:42 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/02 21:43:07 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <sysexits.h>

#include "decompiler.h"
#include "libft.h"
#include "asm.h"
#include "lexer.h"
#include "error.h"
#include "gen.h"

#include "options.h"

#define EXIT_SUCCESS 0
#define EXIT_INVALID_OPTIONS 600

void	compile_file(const char *filename, char *out_filename)
{
	t_assm		assm;
	t_lexeme	*lexems;
	t_lexeme	*lexems_head;
	t_champion	ch;

	assm.filename = filename;
	assm.out_filename = out_filename;
	if ((assm.input_fd = open(assm.filename, O_RDONLY)) < 0)
		print_error(errno, "Can't read source file\n");
	lexems_head = read_lexems(assm.input_fd, assm.filename);
	lexems = lexems_head;
	init_champ(&ch);
	lexems = read_header(lexems, &ch);
	if (!(ch.code = gen_code(lexems, &(ch.code_size))))
		print_warning_format("Code size is null\n");
	free_lexeme_list(&(lexems_head));
	if ((assm.output_fd = open(assm.out_filename, O_CREAT | O_RDWR, 0644)) < 0)
		print_error(errno, "Can't open to write file\n");
	champ_write_to_file(&ch, assm.output_fd);
	free_champ(&ch);
	ft_printf("%s[SUCCESS]%s ", PF_GREEN, PF_EOC);
	ft_printf("Generate %s from %s\n", assm.out_filename, assm.filename);
	ft_strdel(&(assm.out_filename));
}

int		print_usage(void)
{
	ft_printf("OVERVIEW: corewar (42 school project) assembler compiler\n\n");
	ft_printf("USAGE: ./asm [options] <champion.s>  \n\n");
	ft_printf("OPTIONS:\n-w\t\tMake all warnings into errors.\n");
	ft_printf("-h\t\tDisplay available options\n");
	exit(0);
}

int		print_invalid_option(void)
{
	ft_printf("Invalid Option\n");
	exit(EXIT_INVALID_OPTIONS);
}

int		main(int argc, char const *argv[])
{
	int i;
	int options_from_one_arg;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		options_from_one_arg = handle_option_str(argv[i++]);
		if (!options_from_one_arg)
			print_invalid_option();
		g_options |= options_from_one_arg;
	}
	if ((argc < 2) || (g_options & (1 << ('h' - 'a'))))
		print_usage();
	while (i < argc)
	{
		if (argv[i][ft_strlen(argv[i]) - 1] == 's')
			compile_file(argv[i], replace_file_ext(argv[i], ".cor"));
		else if (argv[i][ft_strlen(argv[i]) - 1] == 'r')
			decompile_file(argv[i],
				replace_file_ext(argv[i], ".diasm.s"));
		i++;
	}
	exit(0);
}
