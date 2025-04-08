/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 21:32:22 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/01 21:11:04 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_prep_execute(t_read *line)
// {
// 	int	err;

// 	err = ft_execute_parser(line);
// 	if (err != 0)
// 		return (line->exit_status);
// 	return (0);
// }
void	terminal_shell(t_read *line)
{
	// int err;

	// err = ft_prep_execute(line);
	// if (err != 0)
	// 	ft_exit_with_error(line, "", line->exit_status);
	builtin_part1(line);
}
