/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:44:58 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 07:50:15 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *big, char *little)
{
	size_t	c;
	size_t	size;

	c = 0;
	size = ft_strlen(little);
	if (!big)
	{
		ft_putendl_fd("strstr error: Big doesn't exist", 2);
		return (NULL);
	}
	if (!little)
		return (NULL);
	while (big[c])
	{
		if (ft_strncmp(big + c, little, size) == 0)
			return (big + c);
		c++;
	}
	return (NULL);
}
