/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/28 20:20:12 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_handle_echo(char **cmd)
{
	int i;
	int	endl;

	i = 1;
	endl = 0;
	if (!cmd[i])
	{
		ft_putchar('\n');
		return ;
	}
	if (cmd[i] && ft_strcmp(cmd[i], "-n") == 0)
	{
		i++;
		endl++;
	}
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		i++;
	}
	if (endl == 0)
		ft_putchar('\n');
}
