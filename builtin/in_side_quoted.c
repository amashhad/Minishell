/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_side_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 22:04:25 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

void	count_in_side_quoted(char *str, char c, int *i, int *j)
{
	while (str[*i] != c && str[*i] != '\0')
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
	while (str[(*i)] != c && str[(*i)] != '\0')
	{
		s[(*j)] = str[(*i)];
		(*i)++;
		(*j)++;
	}
	if (str[(*i)] != '\0')
		(*i)++;
}
