/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:56:15 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/07 17:44:30 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_with_error(t_read *line ,char *str)
{
	if (line->prompt != NULL)
		free(line->prompt);
	if (line->cwd != NULL)
		free(line->cwd);
	if (line->enviro && *line->enviro != NULL)
		ft_farray(line->enviro);
	if (line->tokens && *line->tokens != NULL)
		ft_farray(line->tokens);
	if (line->expo && *line->expo != NULL)
		ft_farray(line->expo);
	rl_clear_history();
	if (str)
	{
		free(line->line);
		ft_putendl_fd(str, 2);
	}
	exit(1);
}
