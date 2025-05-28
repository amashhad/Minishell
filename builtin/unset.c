/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:44:24 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 19:25:38 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	ft_handle_unset(t_read *line, char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
		return ;
	while (cmd[i])
	{
		line->expo = ft_subarr(cmd[i], line->expo);
		if (!line->expo)
			ft_exit_with_error(line, "Error in export command", "expo", 1);
		line->enviro = ft_subarr(cmd[i], line->enviro);
		if (!line->enviro)
			ft_exit_with_error(line, "Error in export command", "enviro", 1);
		i++;
	}
}

int	is_odd(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			j++;
		}
		if (str[i] == '\'')
		{
			k++;
		}
		i++;
	}
	if ((j % 2) != 0 || (k % 2) != 0)
		return (1);
	return (0);
}
