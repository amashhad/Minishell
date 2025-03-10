/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/09 16:00:45 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_echo(t_read *line)
{
	int	i;
	int	mode;

	i = 1;
	mode = 0;
	if (ft_strcmp(line->tokens[i], "-n") == 0)
	{
		mode++;
		i++;
	}
	while (line->tokens[i] != NULL)
	{
		if (ft_strcmp(line->tokens[i], "|") == 0)
			return ;
		else if (line->tokens[i + 1] == NULL)
			ft_putstr_fd(line->tokens[i], 1);
		else
			ft_printf("%s ", line->tokens[i]);
		i++;
	}
	if (mode == 0)
		ft_putchar_fd('\n', 1);
}
