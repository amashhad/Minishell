/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:14:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/31 22:36:58 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

// void	builtin_part2(t_read *line)
// {

// }

void	builtin_part1(t_read *line)
{
	if (line->tokens == NULL)
		return ;
	else if (ft_strcmp(line->tokens[0], "env") == 0)
		ft_handle_env(line);
	else if (ft_strcmp(line->tokens[0], "clear") == 0)
	{
		rl_clear_display(0, 0);
		ft_putendl_fd("", 1);
	}
	else if (ft_strcmp(line->tokens[0], "pwd") == 0)
	{
		ft_get_prompt(line);
		ft_putendl_fd(line->cwd, 1);
	}
	else if (ft_strcmp(line->tokens[0], "export") == 0)
		ft_handle_export(line);
	else if (ft_strcmp(line->tokens[0], "unset") == 0)
		ft_handle_unset(line);
	else if (ft_strcmp(line->tokens[0], "cd") == 0)
		ft_handle_cd(line);
	else if (ft_strcmp(line->tokens[0], "echo") == 0)
		ft_handle_echo(line);
	else
	{
		ft_printf("%s: command not found\n", line->tokens[0]);
		line->exit_status = 127;
	}
}

