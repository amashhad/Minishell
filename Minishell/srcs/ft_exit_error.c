/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:56:15 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 09:23:07 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_with_error(t_read *line, char *str, int i)
{
	int	j;

	if (line->pand)
	 	ft_free_expander(line->pand);
	if (line->enviro)
		ft_farray(line->enviro);
	if (line->token)
		ft_free_tokenizer(line->token);
	if (line->piper != NULL)
		free_piper(line);
	if (line->prompt != NULL)
		free(line->prompt);
	if (line->cwd != NULL)
		free(line->cwd);
	if (line->expo != NULL)
		ft_farray(line->expo);
	rl_clear_history();
	if (str)
	{
		//ft_farray(line->tokens);
		free(line->line);
		ft_putendl_fd(str, 2);
	}
	if (line->exit_status == 0)
		line->exit_status = i;
	j = i;
	free (line);
	exit(j);
}
