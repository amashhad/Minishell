/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:44:24 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/31 22:37:44 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_handle_unset(t_read *line)
{
	int	i;

	i = 0;
	if (line->tokens[1] == NULL)
		return ;
	if (ft_strcmp(line->tokens[1], "|") == 0)
		return ;
	while (line->tokens[i])
	{
		line->expo = ft_subarr(line->tokens[i], line->expo);
		if (!line->expo)
			ft_exit_with_error(line, "Error in export command", 1);
		line->enviro = ft_subarr(line->tokens[i], line->enviro);
		if (!line->enviro)
			ft_exit_with_error(line, "Error in export command", 1);
		i++;
	}
}
