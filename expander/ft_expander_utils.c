/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:31:31 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 08:17:58 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	fill_value_expander(t_expand *pand, char *value)
{
	int	i;

	if (value)
	{
		i = 0;
		while (value[i] != '\0')
		{
			pand->result[pand->i_result] = value[i];
			i++;
			pand->i_result++;
		}
	}
}

void	single_quoted(t_expand *pand)
{
	if (pand->input[pand->i] == '\'')
	{
		pand->j = pand->i;
		pand->i++;
		pand->count++;
		while (pand->input[pand->i] != '\''
			&& pand->input[pand->i] != '\0')
		{
			pand->count++;
			pand->i++;
			pand->k++;
		}
		if (pand->input[pand->i] == '\0')
		{
			pand->count--;
			pand->i--;
		}
		pand->quoted = get_string_expander(pand);
		pand->string = NULL;
	}
}

char	*get_string_expander(t_expand *pand)
{
	pand->string = ft_calloc(pand->k + 1, sizeof(char));
	if (!pand->string)
	{
		pand->i_malloc = 1;
		return (NULL);
	}
	pand->k = 0;
	while (pand->j <= pand->i)
	{
		pand->string[pand->k] = pand->input[pand->j];
		pand->k++;
		pand->j++;
	}
	pand->string[pand->k] = '\0';
	return (pand->string);
}

//remove the usage of (getenv) inside the function
//var_expander and replace it with ft_getenv(line.env)
void	var_expander(t_expand *pand)
{
	pand->j = pand->i + 1;
	while (string_expander(pand->input[pand->i + 1]))
	{
		pand->k++;
		pand->i++;
	}
	pand->var_name = get_string_expander(pand);
	if (pand->var_name != NULL)
	{
		pand->var_value = ft_getenv(pand->envment, pand->var_name);
		free (pand->var_name);
	}
	pand->var_name = NULL;
	pand->string = NULL;
	pand->count += ft_strlen(pand->var_value);
	pand->count--;
}
