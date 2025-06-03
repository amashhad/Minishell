/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:14:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 13:21:17 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	builtin_part2(t_read *line, char **cmd)
{
	char	*str;

	str = token_without_quoted(cmd[0]);
	if (ft_strcmp(str, "export") == 0)
	{
		ft_handle_export(line, cmd);
		free (str);
		return (line->exit_status);
	}
	else if (ft_strcmp(str, "unset") == 0)
	{
		ft_handle_unset(line, cmd);
		free (str);
		return (line->exit_status);
	}
	else
	{
		free (str);
		return (10);
	}
}

int	builtin_part4(t_read *line, char **cmd)
{
	char	*str;

	str = token_without_quoted(cmd[0]);
	if (ft_strcmp(str, "pwd") == 0)
	{
		ft_get_prompt(line);
		ft_putendl_fd(line->cwd, 1);
		free (str);
		return (line->exit_status);
	}
	else
	{
		free (str);
		return (builtin_part2(line, cmd));
	}
}

int	builtin_part3(t_read *line, char **cmd)
{
	char	*str;

	str = token_without_quoted(cmd[0]);
	if (ft_strcmp(str, "cd") == 0)
	{
		ft_handle_cd(line, cmd);
		free (str);
		return (line->exit_status);
	}
	else if (ft_strcmp(str, "echo") == 0)
	{
		ft_handle_echo(cmd);
		free (str);
		return (line->exit_status);
	}
	else
	{
		free (str);
		return (builtin_part4(line, cmd));
	}
}

int	builtin_part1(t_read *line, char **cmd)
{
	char	*str;

	str = NULL;
	if (!cmd[0])
		return (0);
	str = token_without_quoted(cmd[0]);
	if (str == NULL || str[0] == '\0')
	{
		free(str);
		line->exit_status = 127;
		return (0);
	}
	else if (ft_strcmp(str, "env") == 0)
	{
		ft_handle_env(line, cmd);
		free (str);
		return (line->exit_status);
	}
	free (str);
	return (builtin_part3(line, cmd));
}
