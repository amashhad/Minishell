/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_and_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:18:04 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 18:14:24 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	**fill_env(char *str, char **old_arr)
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
	arr[size + 1] = NULL;
	return (arr);
}
