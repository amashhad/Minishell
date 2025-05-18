/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:27:31 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/13 19:21:22 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	count_arrow_var_name(t_expand *pand)
{
	pand->i++;
	pand->count++;
	if (ft_isdigit(pand->input[pand->i + 1]))
		pand->i_malloc = 1;
	while (string_expander(pand->input[pand->i + 1]))
	{
		pand->i++;
		pand->count++;
	}
}

void	count_arrow(t_expand *pand)
{
	if (pand->input[pand->i] == '>')
	{
		if (pand->input[pand->i + 1] == '>' || pand->input[pand->i + 1] == ' ')
		{
			pand->i++;
			pand->count++;
		}
		if (pand->input[pand->i + 1] == '$')
			count_arrow_var_name(pand);
	}
	if (pand->input[pand->i] == '<')
	{
		if (pand->input[pand->i + 1] == '<' || pand->input[pand->i + 1] == ' ')
		{
			pand->i++;
			pand->count++;
		}
		if (pand->input[pand->i + 1] == '$')
			count_arrow_var_name(pand);
	}
}

void	fill_arrow_var_name(t_expand *pand)
{
    pand->i++;
	pand->i_result++;
    pand->result[pand->i_result] = pand->input[pand->i];
	if (ft_isdigit(pand->input[pand->i + 1]))
		pand->i_malloc = 1;
	while (string_expander(pand->input[pand->i + 1]))
	{
		pand->i++;
		pand->i_result++;
        pand->result[pand->i_result] = pand->input[pand->i];
	}
}

void	fill_arrow(t_expand *pand)
{
	if (pand->input[pand->i] == '>')
	{
		pand->result[pand->i_result] = pand->input[pand->i];
		if (pand->input[pand->i + 1] == '>' || pand->input[pand->i + 1] == ' ')
		{
			pand->i++;
			pand->i_result++;
            pand->result[pand->i_result] = pand->input[pand->i];
		}
		if (pand->input[pand->i + 1] == '$')
			fill_arrow_var_name(pand);
	}
	if (pand->input[pand->i] == '<')
	{
		pand->result[pand->i_result] = pand->input[pand->i];
		if (pand->input[pand->i + 1] == '<' || pand->input[pand->i + 1] == ' ')
		{
			pand->i++;
			pand->i_result++;
            pand->result[pand->i_result] = pand->input[pand->i];
		}
		if (pand->input[pand->i + 1] == '$')
			fill_arrow_var_name(pand);
	}
}
