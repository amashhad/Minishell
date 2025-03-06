/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:47:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/06 17:53:38 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_export(t_read *line)
{
	if (ft_strncmp(line->tokens[0], "export", 6) == 0)
	{
		if (line->tokens[1] != NULL)
		{
			if (ft_strchr(line->tokens[1], '|') == NULL)
				line->expo = ft_addarr(line->tokens[1], line->expo);
			else
				ft_addprintarr("declare -x ", line->expo);
		}
		else
			ft_addprintarr("declare -x ", line->expo);
	}
	else
	{
		if (line->tokens[1] != NULL && (ft_strchr(line->tokens[1], '|') == NULL))
			line->expo = ft_subarr(line->tokens[1], line->expo);
		else
			return ;
	}
}
void	ft_handle_cd(t_read *line)
{
	if (line->tokens[1] != NULL)
	{
		if (ft_strchr(line->tokens[1], '|') == NULL)
		{
		}
	}
}
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
		ft_handle_export(line);
	else if (ft_strncmp(line->tokens[0], "cd", 2) == 0)
		ft_handle_cd(line);
	else
		return ;
}
