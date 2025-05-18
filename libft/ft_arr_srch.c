/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_srch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:27:15 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/01 23:44:41 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//searches the array, and returns the first occurance of str in it
//returns it disregarding index (starts at 1)
//returns (-1) on error
//MUST SEND NULL TERMINATED ARRAY!!!!!
int	ft_arr_srch(char *str, char **arr)
{
	int	i;

	i = 0;
	if (!str || !arr)
		return (-1);
	while (arr[i])
	{
		if (ft_strcmp(arr[i], str) == 0)
			break ;
		i++;
	}
	if (arr[i] == NULL)
		return (0);
	else
		return (i + 1);
}
