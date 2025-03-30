/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:31:31 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/30 22:40:50 by amashhad         ###   ########.fr       */
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
