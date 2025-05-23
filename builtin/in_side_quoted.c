/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_side_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/22 18:25:29 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	count_in_side_quoted(char *str, char c, int *i, int *j)
{
	while ((str[*i] != c || (str[*i] == c && str[*i - 1] == '\\'))
		&& str[*i] != '\0')
	{
		(*i)++;
		(*j)++;
	}
	if (str[*i] != '\0')
		(*i)++;
}

void	fill_in_side_quoted(char *str, char *s, int *i, int *j)
{
	char	c;

	c = str[(*i)];
	(*i)++;
	while ((str[(*i)] != c || (str[(*i)] == c && str[(*i) - 1] == '\\'))
		&& str[(*i)] != '\0')
	{
		s[(*j)] = str[(*i)];
		(*i)++;
		(*j)++;
	}
	if (str[(*i)] != '\0')
		(*i)++;
}
