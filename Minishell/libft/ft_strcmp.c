/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:14:59 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/19 20:45:55 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns the difference between s1 and s2
//returns positive number or (0) on success
//returns (-1) on failure
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			if (s1[i] > s2[i])
				return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
			else
				return ((unsigned char)(s2[i]) - (unsigned char)(s1[i]));
		}
		i++;
	}
	if (s1[i] > s2[i])
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	else
		return ((unsigned char)(s2[i]) - (unsigned char)(s1[i]));
}
