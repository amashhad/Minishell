/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:44:12 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/25 21:59:00 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**edit_arr(char **arr, char **new_arr, char *str)
{
	int	i;
	int	j;
	int	limit;

	i = 0;
	j = 0;
	limit = 1;
	while (arr[i])
	{
		if (limit > 0 && ft_strstr(arr[i], str))
			limit--;
		else
		{
			new_arr[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	new_arr[j] = NULL;
	return (new_arr);
}

//removes the first occurance of the string (str) in the array (arr)
//frees the previous array and returns the changed version of the array
//returns NULL on error, returns the same array in case str doesn't exist
//or is not found in the provided array
//must send NULL terminated array
char	**del_arr(char **arr, char *str)
{
	char	**new_arr;

	new_arr = NULL;
	if (!arr || !*arr)
		return (NULL);
	if (!str || !ft_fetcharr(arr, str))
		return (arr);
	new_arr = malloc(sizeof(char *) * ft_arrlen(arr));
	if (!new_arr)
	{
		perror("malloc");
		return (arr);
	}
	new_arr = edit_arr(arr, new_arr, str);
	ft_farray(arr);
	return (new_arr);
}
