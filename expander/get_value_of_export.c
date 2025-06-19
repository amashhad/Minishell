/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_of_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/20 01:05:17 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

char	*get_value_of_export(const char *big, const char *little)
{
	size_t	c;

	c = 0;
	if (!big)
	{
		ft_putendl_fd("(get_value_of_export error)", 2);
		exit(1);
	}
	if (!*little)
		return (NULL);
	while (little[c] != '\0')
	{
		if (big[c] == little[c])
			c++;
		else if (big[c] != little[c])
			return (NULL);
	}
	if (big[c] == '=')
		return ((char *)(big + (c + 1)));
	return (NULL);
}
