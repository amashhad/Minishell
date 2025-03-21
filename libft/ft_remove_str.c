/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:40:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/20 14:24:36 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//removes the string (rm) from the string (str)
//returns the same string, as it will free and realloc it
//returns (NULL) on errors and frees the string
//returns the string if rm is empty
char	*ft_remove_str(char *str, char *rm)
{
	int	i;
	char	*found;

	i = 0;
	if (!str)
		return (NULL);
	if (!rm)
		return (str);
	found = ft_strnstr(str, rm, ft_strlen(str));
	if (!found)
		return (NULL);
	free(str);
	return (found);
}
