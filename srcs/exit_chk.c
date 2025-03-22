/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_chk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 22:59:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 03:56:40 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_numeric(int i, t_read *line)
{
	int		srch;

	srch = 0;
	if (!line->tokens[i])
		return (1);
	while (line->tokens[i][srch] && ft_isdigit(line->tokens[i][srch]))
		srch++;
	if (line->tokens[i][srch] && !ft_isdigit(line->tokens[i][srch]))
	{
		line->exit_status = 2;
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(line->tokens[i], 2);
		ft_putendl_fd(" : numeric argument required", 2);
		return (1);
	}
	line->exit_status = ft_atoi(line->tokens[i]);
	i++;
	if (line->tokens[i])
	{
		line->exit_status = 1;
		ft_putendl_fd("Minishell: exit: too many arguments", 2);
		return (0);
	}
	return (1);
}

int	ft_exit_shell(t_read *line)
{
	int	i;

	i = 0;
	if (!line->line)
	{
		line->exit_status = 0;
		return (1);
	}
	if (!line->tokens)
		return (0);
	if (ft_strcmp(line->tokens[i], "exit") == 0
			|| ft_strcmp(line->tokens[i], "'exit'"))
	{
		i++;
		i = ft_numeric(i, line);
		return (i);
	}
	return (0);
}
