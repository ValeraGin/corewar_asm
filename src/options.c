/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmathew <hmathew@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:20:51 by hmathew           #+#    #+#             */
/*   Updated: 2020/02/26 20:14:23 by hmathew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		handle_option_str(char *option_str)
{
	int	wi;
	int options;

	wi = 1;
	options = 0;
	while (option_str[wi])
	{
		if ('a' <= option_str[wi] && option_str[wi] <= 'z')
			options |= 1 << (option_str[wi] - 'a');
		wi++;
	}
	return (options);
}
