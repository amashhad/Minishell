/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_of_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:59:19 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 09:13:56 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_value_of_export(const char *big, const char *little, size_t len)
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
	if (len == 0)
		return (NULL);
	while (little[c] != '\0')
	{
		if (big[c] == little[c])
			c++;
		else if (big[c] != little[c] && big[c] != '=')
			return (NULL);
	}
	if (big[c] == '=')
		return ((char *)(big + (c + 1)));
	return (NULL);
}
