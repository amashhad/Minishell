/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:27:31 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/07 22:01:59 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	initialize_pand(t_expand *pand)
{
	pand->i = 0;
	pand->i_result = 0;
	pand->i_size = 0;
	pand->count = 0;
	pand->j = 0;
	pand->count = 0;
	pand->k = 0;
	pand->i_malloc = 0;
	pand->last_exit_code = NULL;
	pand->string = NULL;
	pand->argv = NULL;
	pand->quoted = NULL;
	pand->input = NULL;
	pand->var_name = NULL;
	pand->var_value = NULL;
	pand->result = NULL;
}

void	ft_free_expander(t_expand *pand)
{
	if (pand)
	{
		if (pand->var_value)
			free (pand->var_value);
		if (pand->last_exit_code)
			free (pand->last_exit_code);
		if (pand->var_name)
			free (pand->var_name);
		if (pand->string)
			free (pand->string);
		if (pand->quoted)
			free (pand->quoted);
		free (pand);
	}
}
	
	