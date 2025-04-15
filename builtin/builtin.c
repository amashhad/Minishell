/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:14:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/15 00:24:40 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	builtin_part2(t_read *line, char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		ft_handle_export(line, cmd);
		return (line->exit_status);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_handle_unset(line, cmd);
		return (line->exit_status);
	}
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		ft_handle_cd(line, cmd);
		return (line->exit_status);
	}
	else if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_handle_echo(cmd);
		return (line->exit_status);
	}
	else
		return (1);
}

int	builtin_part1(t_read *line, char **cmd)
{
	int	executed;

	executed = 0;
	if (cmd == NULL)
		return (1);
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_handle_env(line, cmd);
		return (line->exit_status);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_get_prompt(line);
		ft_putendl_fd(line->cwd, 1);
		return (line->exit_status);
	}
	else
		executed = builtin_part2(line, cmd);
	return (executed);
}
