/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:40:44 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/27 22:23:11 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//removes the string (rm) from the string (str)
//returns the same string, as it will free and realloc it
//returns (NULL) on errors and frees the string
//returns the string if rm is empty
char	*ft_remove_str(char *str, char *rm)
{
	int		srch;
	int		fnd;
	char	*ret;

	srch = 0;
	fnd = 0;
	if (!str)
		return (NULL);
	if (!rm && !*rm)
		return (str);
	while (str[srch] != '\0')
	{
		if (rm[fnd] == '\0')
		{
			ret = ft_strdup(str + srch);
			free(str);
			return (ret);
		}
		if (str[srch] && str[srch] == rm[fnd])
			fnd++;
		else
			fnd = 0;
		srch++;
	}
	return (str);
}
