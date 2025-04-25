/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 06:13:00 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/24 07:11:07 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	exit_message(t_read *line)
{
	int		exit_status;
	char	*str;

	exit_status = line->exit_status;
	str = strerror(line->exit_status);
	perror(str);
	free(str);
	free(line->line);
	exit(exit_status);
}
void	execution_free(t_read *line)
{
	if (line->pand)
		ft_free_expander(line->pand);
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
	exit_message(line);
}
