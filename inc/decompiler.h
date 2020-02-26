/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompiler.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:53:24 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 21:58:03 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECOMPILER_H
# define DECOMPILER_H

# include "op.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int		decompile_file(int options, const char *filename, char *out_filename);

#endif
