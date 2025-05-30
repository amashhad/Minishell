/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fill_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:33:23 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/30 12:25:43 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

static void	dollar_string_expander(t_expand *pand)
{
	if (!(string_expander(pand->input[pand->i + 1])))
	{
		if (comper_expander(pand->input[pand->i + 1]))
		{
			pand->result[pand->i_result] = pand->input[pand->i];
			pand->i_result++;
			pand->i++;
		}
		else
			pand->i += 2;
	}
	else if (!(comper_expander(pand->input[pand->i + 1])))
	{
		var_expander(pand);
		pand->i++;
		fill_value_expander(pand, pand->var_value);
	}
	else
	{
		pand->result[pand->i_result] = pand->input[pand->i];
		pand->i_result++;
		pand->i++;
	}
}

void	dollar_fill_expander(t_expand *pand)
{
	if (pand->input[pand->i + 1] == '?')
	{
		pand->i += 2;
		fill_value_expander(pand, pand->last_exit_code);
	}
	else if (pand->input[pand->i + 1] == '$')
	{
		pand->i += 2;
		fill_value_expander(pand, "$$");
	}
	else if (pand->input[pand->i + 1] == '0')
	{
		pand->i += 2;
		fill_value_expander(pand, pand->argv);
	}
	else if (ft_isdigit(pand->input[pand->i + 1]))
		pand->i += 2;
	else
		dollar_string_expander(pand);
}

static void	dollar_malloc_string(t_expand *pand)
{
	if (ft_isdigit(pand->input[pand->i + 1]))
	{
		pand->count -= 1;
		pand->i += 1;
	}
	else if (!(string_expander(pand->input[pand->i + 1])))
	{
		if (!(comper_expander(pand->input[pand->i + 1])))
		{
			pand->count -= 1;
			pand->i += 1;
		}
	}
	else if (!(comper_expander(pand->input[pand->i + 1])))
		var_expander(pand);
}

void	dollar_malloc_expander(t_expand *pand)
{
	if (pand->input[pand->i + 1] == '?')
	{
		pand->count += ft_strlen(pand->last_exit_code);
		pand->count -= 1;
		pand->i++;
	}
	else if (pand->input[pand->i + 1] == '$')
	{
		pand->count += 1;
		pand->i++;
	}
	else if (pand->input[pand->i + 1] == '0')
	{
		pand->count += ft_strlen(pand->argv);
		pand->count -= 1;
		pand->i++;
	}
	else
		dollar_malloc_string(pand);
}

size_t	count_malloc(t_expand *pand)
{
	while (pand->input[pand->i] != '\0')
	{
		if (pand->input[pand->i] == '>' || pand->input[pand->i] == '<')
			count_arrow(pand);
		if (pand->input[pand->i] == '$')
			dollar_malloc_expander(pand);
		if (pand->input[pand->i] == '"')
			double_quoted(pand);
		single_quoted(pand);
		if (pand->quoted)
		{
			free (pand->quoted);
			pand->quoted = NULL;
		}
		pand->count++;
		pand->i++;
	}
	return (pand->count);
}
