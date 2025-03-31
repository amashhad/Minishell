/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:09:59 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/31 22:37:51 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_handle_env(t_read *line)
{
	if (line->tokens[1] != NULL)
	{
		ft_putstr_fd("env: `", 2);
		ft_putstr_fd(line->tokens[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		line->exit_status = 127;
	}
	else
		ft_printarr(line->enviro);
}
