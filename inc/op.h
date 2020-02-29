/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/02/29 14:48:00 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define REG_CHAR				'r'
# define CMD_CHAR				'.'
# define STRING_CHAR			'\"'

# define CMD_PREF_SIZE			1

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3

/*
**	# define MAX_ARG_SIZE
**	(FT_MAX(FT_MAX(IND_SIZE, REG_SIZE), DIR_SIZE))
**	# define MAX_STATEMENT_SIZE
**	(MAX_ARGS_NUMBER*MAX_ARG_SIZE)+OPER_CODE_SIZE+TYPES_CODE_SIZE
*/

# define CHAMP_MAX_SIZE		684
# define MAX_STATEMENT_SIZE	14
# define MAX_ARG_SIZE		18

typedef struct		s_op
{
	char			*name;
	int				count_of_args;
	int				arg_type[3];
	int				op_code;
	int				time_in_cycles;
	char			*describe;
	int				args_code;
	int				short_tdir;
}					t_op;

extern t_op			g_op_tab[17];

#endif
