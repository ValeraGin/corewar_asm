/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 20:04:30 by hmathew           #+#    #+#             */
/*   Updated: 2020/03/01 15:02:57 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct		s_cmd
{
	char			*name;
	int				max_length;
	int				offset;
}					t_cmd;

extern t_cmd		g_cmd_tab[2];

#endif
