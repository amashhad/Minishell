/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:27:08 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/04 22:26:30 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_addarr(char *str, char **arr)
{
	int	i;
	char	**new_arr;

	i = 0;
	if (!str)
	{
		ft_putendl_fd("addarr error, no str present, nothing to add", 2);
		return (NULL);
	}
	if (!arr || *arr == NULL)
	{
		ft_putendl_fd("addarr error, no arr present, nothing to edit", 2);
		return (NULL);
	}
	i = ft_arrlen(arr);
	new_arr = malloc(sizeof(char *) + i + 2);
	return (new_arr);
}
