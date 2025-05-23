/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/22 18:26:31 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	check_quoted(char *str)
{
	size_t	i;
	char	c;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			c = str[i];
			while (str[i] != '\0')
			{
				i++;
				if (str[i] == c)
					break ;
				if (str[i] == '\0')
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	is_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str[i] != '\0')
		{
			while (str[i] == 'n')
				i++;
			if (str[i] == '\0')
				return (1);
			return (0);
		}
	}
	return (0);
}
