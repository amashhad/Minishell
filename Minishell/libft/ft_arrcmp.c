/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:07:28 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/18 21:28:08 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmp_arrsize(char **arr1, char **arr2)
{
	int	size1;
	int	size2;

	size1 = 0;
	size2 = 0;
	if (!arr1 || !arr2)
		return (-1);
	size1 = ft_arrlen(arr1);
	size2 = ft_arrlen(arr2);
	if (size1 > size2)
		return (size1 - size2);
	else
		return (size2 - size1);
}

//compares two arrays, arr1, and arr2, then returns the difference
//if arrays are similar, returns (0), if an error occurs returns (-1)
//two modes are accepted, (0): array to array in size,
//(1): str to str inside array compare.
//MUST SEND NULL TERMINATED ARRAY
int	ft_arrcmp(char **arr1, char **arr2, int mode)
{
	int	i;

	i = 0;
	if (!arr1 || !arr2)
		return (-1);
	if (mode == 0)
		return (ft_cmp_arrsize(arr1, arr2));
	else if (mode == 1)
	{
		while (arr1[i] && arr2[i])
		{
			if (ft_strcmp(arr1[i], arr2[i]) != 0)
				return (ft_strcmp(arr1[i], arr2[i]));
			i++;
		}
		return (0);
	}
	return (-1);
}
