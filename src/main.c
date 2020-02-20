/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 18:03:42 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/20 14:21:39 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <sysexits.h>

#include "libft.h"
#include "asm.h"

#include "lexer.h"

static void	print_usage(void)
{
	ft_printf("Usage: ./asm [-a] [*] <champion.s>\n");
	exit(0);
}

int			compile_file(int options, char *filename, char *out_filename)
{
	t_assm assm;

	assm.options = options;
	assm.filename = filename;
	assm.out_filename = out_filename;

	if ((assm.input_fd = open(assm.filename, O_RDONLY)) < 0)
		print_error("Can't read source file", errno);
	if ((assm.output_fd = open(assm.out_filename, O_CREAT | O_RDWR, 0644)) < 0)
		print_error("Can't open to write file", errno);


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
