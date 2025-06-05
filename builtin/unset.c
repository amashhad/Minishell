/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:44:24 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:23:50 by amashhad         ###   ########.fr       */
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

int	is_valid_export_key(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '=')
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_export_value(const char *str)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (str[i] != '\0')
	{
		while (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				break ;
			i++;
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '|' || str[i] == '&')
			return (1);
		i++;
	}
	return (0);
}
