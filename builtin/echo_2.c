/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:12:16 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	is_n(char *cmd)
{
	char	*str;
	int		i;

	i = 0;
	str = token_without_quoted(cmd);
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
			{
				free (str);
				return (1);
			}
			free(str);
			return (0);
		}
	}
	free(str);
	return (0);
}
