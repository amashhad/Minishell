/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 08:24:53 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/03 01:42:56 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	arr_size(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i] != NULL)
		i++;
	return (i);
}

//returns an allocated copy of the array "arr"
//returns NULL on malloc errors or no Arr sent
//MUST SEND NULL TERMINATED ARR!!
char	**ft_cpyarr(char **arr)
{
	int		size;
	int		i;
	char	**temp;

	i = 0;
	size = arr_size(arr);
	if (!size)
		return (NULL);
	temp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!temp)
	{
		perror("malloc");
		return (NULL);
	}
	while (arr[i] != NULL)
	{
		temp[i] = ft_strdup(arr[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}
