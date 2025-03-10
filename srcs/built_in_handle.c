/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:47:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/09 16:00:16 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_read *line)
{
	if (line->tokens == NULL)
		return ;
	else if (ft_strncmp(line->tokens[0], "env", 3) == 0)
		ft_printarr(line->enviro);
	else if (ft_strncmp(line->tokens[0], "pwd", 3) == 0)
	{
		ft_get_prompt(line);
		ft_putendl_fd(line->cwd, 1);
	}
	else if (ft_strncmp(line->tokens[0], "export", 6) == 0)
		ft_handle_export(line);
	else if (ft_strncmp(line->tokens[0], "unset", 5) == 0)
		ft_handle_unset(line);
	else if (ft_strncmp(line->tokens[0], "cd", 2) == 0)
		ft_handle_cd(line);
	else if (ft_strncmp(line->tokens[0], "echo", 5) == 0)
	{
		if (!line->tokens[1])
			ft_putstr("");
		else
			ft_handle_echo(line);
	}
	else
		ft_printf("%s: command not found\n", line->tokens[0]);
}
