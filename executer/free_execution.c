/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 06:13:00 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 03:55:01 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	exit_message(int exit_stat, char *msg)
{
	if (!msg)
		exit(exit_stat);
	ft_putendl_fd(msg, 2);
	free(msg);
	exit(exit_stat);
}

void	execution_free(t_read *line, int exit_stat, char *msg)
{
	if (line->token)
		ft_free_tokenizer(line->token);
	if (line->prompt != NULL)
		free(line->prompt);
	if (line->cwd != NULL)
		free(line->cwd);
	if (line->enviro != NULL)
		ft_farray(line->enviro);
	if (line->expo != NULL)
		ft_farray(line->expo);
	if (line->piper)
		free_piper(line);
	if (line->pand)
		ft_free_expander(line->pand);
	free(line->line);
	rl_clear_history();
	exit_message(exit_stat, msg);
}
