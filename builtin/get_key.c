/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:35:56 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*get_key(char *str)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	s = ft_calloc(i + 1, sizeof(char));
	if (!s)
	{
		free (s);
		return ("Malloc Error\n");
	}
	i = 0;
	while (str[i] != '=')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
