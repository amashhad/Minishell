/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/07 17:32:39 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_export(t_read *line)
{
	if (line->tokens[1] == NULL)
	{
		ft_addprintarr("declare -x ", line->expo);
		return ;
	}
	if (line->tokens[1] != NULL)
	{
		if (ft_strcmp(line->tokens[1], "|"))
			line->expo = ft_addarr(line->tokens[1], line->expo);
		else if(ft_strcmp(line->tokens[1], "|") == 0)
			return ;
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
