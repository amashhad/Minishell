/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/26 16:45:32 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_handle_echo(t_read *line)
{
	int i;
	int	endl;

	i = 1;
	endl = 0;
	if (!line->tokens[i])
	{
		ft_putchar('\n');
		return ;
	}
	if (ft_arr_srch("|", line->tokens) > 1)
		return ;
	if (line->tokens[i] && ft_strcmp(line->tokens[i], "-n") == 0)
	{
		i++;
		endl++;
	}
	while (line->tokens[i])
	{
		ft_putstr(line->tokens[i]);
		i++;
	}
	if (endl == 0)
		ft_putchar('\n');
}
