/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:35:44 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static char	*fill_str(char *str, char *arr, int i, int j)
{
	while (arr[i] != '=')
	{
		str[j] = arr[i];
		j++;
		i++;
	}
	str[j] = arr[i];
	i++;
	j++;
	str[j] = '"';
	j++;
	while (arr[i] != '\0')
	{
		str[j] = arr[i];
		j++;
		i++;
	}
	str[j] = '"';
	j++;
	str[j] = '\0';
	return (str);
}

void	*add_quoted_for_value(char **arr, int size)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(arr[size]);
	str = malloc((len + 3) * sizeof(char));
	if (!str)
		return (NULL);
	str = fill_str(str, arr[size], i, j);
	free(arr[size]);
	arr[size] = ft_strdup(str);
	free (str);
	return (NULL);
}

char	**fill_export(char *str, char **old_arr)
{
	int		i;
	int		size;
	char	**arr;

	i = 0;
	size = ft_arrlen(old_arr);
	arr = malloc(sizeof(char *) * (size + 2));
	if (!arr)
		return (NULL);
	while (old_arr[i] != NULL)
	{
		arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	ft_farray(old_arr);
	arr[i] = ft_strdup(str);
	add_quoted_for_value(arr, size);
	arr[size + 1] = NULL;
	return (arr);
}
