/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:56:15 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 08:51:05 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_msg(t_read *line, char *str, int i)
{
	int	j;

	j = 0;
	if (str)
	{
		free(line->line);
		ft_putendl_fd(str, 2);
	}
	if (line->exit_status == 0)
		line->exit_status = i;
	j = i;
	free (line);
	exit(j);
}

void	ft_exit_with_error(t_read *line, char *str, char *exception, int i)
{
	if (line->pand && ft_strcmp(exception, "pand"))
		ft_free_expander(line->pand);
	if (line->enviro && ft_strcmp(exception, "enviro"))
		ft_farray(line->enviro);
	if (line->token && ft_strcmp(exception, "token"))
		ft_free_tokenizer(line->token);
	if (line->piper != NULL && ft_strcmp(exception, "piper"))
		free_piper(line);
	if (line->prompt != NULL && ft_strcmp(exception, "prompt"))
		free(line->prompt);
	if (line->cwd != NULL && ft_strcmp(exception, "cwd"))
		free(line->cwd);
	if (line->expo != NULL && ft_strcmp(exception, "expo"))
		ft_farray(line->expo);
	rl_clear_history();
	ft_msg(line, str, i);
}
