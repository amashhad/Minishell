/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 06:13:00 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/28 22:50:22 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	exit_message(t_read *line)
{
	int		exit_status;
	char	*str;

	str = NULL;
	exit_status = line->exit_status;
	if (line->exit_status != 0)
	{
		str = strerror(line->exit_status);
		perror(str);
	}
	exit(exit_status);
}
void	execution_free(t_read *line)
{
	// if (line->pand)
		// ft_free_expander(line->pand);
	if (line->token)
		ft_free_tokenizer(line->token);
	// if (line->piper != NULL)
	// 	free_piper(line);
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
