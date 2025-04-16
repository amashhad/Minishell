/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:14:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 11:04:09 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

// void	builtin_part2(t_read *line)
// {

// }

void	builtin_part1(t_read *line, char **cmd)
{
	if (cmd == NULL)
		return ;
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_handle_env(line, cmd);
	else if (ft_strcmp(cmd[0], "clear") == 0)
	{
		rl_clear_display(0, 0);
		ft_putendl_fd("", 1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		ft_get_prompt(line);
		ft_putendl_fd(line->cwd, 1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_handle_export(line, cmd);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_handle_unset(line, cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_handle_cd(line, cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_handle_echo(cmd);
	else
		return ;
}

