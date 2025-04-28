/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 06:08:46 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/28 18:23:45 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	if (!big)
	{
		ft_putendl_fd("(Strnstr error, no 'big')", 2);
		exit(1);
	}
	if (!*little)
		return (NULL);
	if (len == 0)
		return (NULL);
	while (little[c] != '\0')
	{
		if (big[c] == little[c])
		{
			c++;
		}
		else if (big[c] != little[c] && big[c] != '=')
		{
			return (NULL);
		}
	}
	if (big[c] == '=')
	{
		return ((char *)(big + (c + 1)));
	}
	return (NULL);
	/*while (i < len && big[i])
	{
		c = 0;
		while (big[i + c] == little[c] && (i + c) < len && big[i + c])
			c++;
		if (little[c] == '\0')
			return ((char *)(big + i));
		i++;
	}*/
	return (0);
}
