/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fetcharr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:53:51 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 09:13:00 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//fetches the string from the array and returns a pointer to it
//if no such string exists within array returns null
//no array or fetch exist returns null
//MUST SEND NULL TERMINATED ARRAY
//no need to free memory
char	*ft_fetcharr(char **arr, char *fetch)
{
	int		i;
	char	*fnd;

	i = 0;
	fnd = NULL;
	if (!fetch)
		return (NULL);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		if (ft_strstr(arr[i], fetch))
		{
			fnd = ft_strstr(arr[i], fetch);
			return (fnd);
		}
		i++;
	}
	return (NULL);
}
