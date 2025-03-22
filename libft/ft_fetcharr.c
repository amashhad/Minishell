/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fetcharr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:53:51 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 06:59:09 by amashhad         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (!fetch)
		return (NULL);
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		if (ft_strnstr(arr[i], fetch, ft_strlen(fetch)))
			return (ft_strnstr(arr[i], fetch, ft_strlen(fetch)));
		i++;
	}
	return (NULL);
}
