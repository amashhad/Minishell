/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_compare_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:32:26 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 13:34:26 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	comper_expander(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '$')
		return (1);
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	string_expander(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	double_quoted(t_expand *pand)
{
	if (pand->input[pand->i] == '"')
	{
		pand->i++;
		pand->count++;
		while (pand->input[pand->i] != '"'
			&& pand->input[pand->i] != '\0')
		{
			if (pand->input[pand->i] == '$')
				dollar_malloc_expander(pand);
			pand->count++;
			pand->i++;
		}
		if (pand->input[pand->i] == '\0')
		{
			pand->count--;
			pand->i--;
		}
	}
}
