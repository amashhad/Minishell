/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:47:43 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/05 23:51:29 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin(t_read *line)
{
	if (line->tokens != NULL && (ft_strncmp(line->tokens[0], "env", 3) == 0))
		ft_printarr(line->enviro);
	if (line->tokens != NULL && (ft_strncmp(line->tokens[0], "pwd", 3) == 0))
	{
		ft_get_prompt(line);
		ft_putendl_fd(line->cwd, 1);
	}
	if (line->tokens != NULL && (ft_strncmp(line->tokens[0], "export", 6) == 0))
		ft_addprintarr("declare -x ", line->enviro);
}
