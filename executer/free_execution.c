/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 06:13:00 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/30 23:52:51 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	exit_message(int exit_stat)
{
	char	*str;

	str = NULL;
	if (exit_stat != 0)
	{
		str = strerror(exit_stat);
		perror(str);
	}
	exit(exit_stat);
}
void	execution_free(t_read *line, int exit_stat)
{
	if (line->token)
		ft_free_tokenizer(line->token);
	if (line->piper != NULL)
		free_piper(line);
	if (line->prompt != NULL)
		free(line->prompt);
	if (line->cwd != NULL)
		free(line->cwd);
	if (line->enviro != NULL)
		ft_farray(line->enviro);
	if (line->expo != NULL)
		ft_farray(line->expo);
	free(line->line);
	rl_clear_history();
	exit_message(exit_stat);
}
