/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpynarr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 03:13:51 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 03:21:19 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns an allocated copy of the array "arr" up to 'n' size
//returns full array if arr_size < n
//returns NULL on malloc errors or no Arr sent
//MUST SEND NULL TERMINATED ARR!!
char	**ft_cpynarr(char **arr, int n)
{
	int		size;
	int		i;
	char	**temp;

	i = 0;
	size = ft_arrlen(arr);
	if (!size)
		return (NULL);
	if (size < n)
		n = size;
	temp = (char **)malloc(sizeof(char *) * (n + 1));
	if (!temp)
		return (NULL);
	while (i < n)
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[n] = NULL;
	return (temp);
}
