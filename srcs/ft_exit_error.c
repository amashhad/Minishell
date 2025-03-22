/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:56:15 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 02:21:55 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_with_error(t_read *line ,char *str)
{
	if (line->prompt != NULL)
		free(line->prompt);
	if (line->cwd != NULL)
		free(line->cwd);
	if (line->enviro != NULL)
		ft_farray(line->enviro);
	if (line->expo != NULL)
		ft_farray(line->expo);
	rl_clear_history();
	if (str)
	{
		ft_farray(line->tokens);
		free(line->line);
		ft_putendl_fd(str, 2);
	}
	exit(line->exit_status);
}
