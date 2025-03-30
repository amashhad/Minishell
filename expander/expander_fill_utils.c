/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fill_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:33:23 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/30 22:41:15 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	dollar_string_expander(t_expand *pand)
{
	if (!(string(pand->input[pand->i + 1])))
	{
		if (comper(pand->input[pand->i + 1]))
		{
			pand->result[pand->i_result] = pand->input[pand->i];
			pand->i_result++;
			pand->i++;
		}
		else
			pand->i += 2;
	}
	else if (!(comper(pand->input[pand->i + 1])))
	{
		var(pand);
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
	else if (ft_is_digit(pand->input[pand->i + 1]))
		pand->i += 2;
	else
		dollar_string_expander(pand);
}
