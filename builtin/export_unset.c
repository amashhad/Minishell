/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 09:43:22 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_export_err(t_read *line, int errno, char *str)
{
	line->exit_status = errno;
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	ft_handle_export(t_read *line)
{
	int	i;

	i = 1;
	if (line->tokens[i] == NULL)
	{
		ft_addprintarr("declare -x ", line->expo);
		return ;
	}
	if (ft_arr_srch( "|", line->tokens) != 0)
		return ;
	while (line->tokens[i] != NULL)
	{
		if (ft_strncmp(line->tokens[i], "=", 1) == 0)
			ft_export_err(line, 1, line->tokens[i]);
		else
		{
			line->enviro = ft_addarr(line->tokens[i], line->enviro);
			line->expo = ft_addarr(line->tokens[i], line->expo);
		}
		i++;
	}
}
void	ft_handle_unset(t_read *line)
{
	if (line->tokens[1] == NULL)
		return ;
	if (ft_strcmp(line->tokens[1], "|") == 0)
		return ;
	else
	{
		line->expo = ft_subarr(line->tokens[1], line->expo);
		if (!line->expo)
			ft_exit_with_error(line, "Error in export command");
		line->enviro = ft_subarr(line->tokens[1], line->enviro);
		if (!line->enviro)
			ft_exit_with_error(line, "Error in export command");
	}
}
