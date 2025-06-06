/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 00:20:24 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/01 20:23:13 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(int c)
{
	if ((c == '\f') || (c == '\n') || (c == '\r')
		|| (c == '\t') || (c == '\v')
		|| (c == ' '))
		return (1);
	return (0);
}
