/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_compare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:45:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 14:33:24 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

int	chk_compare(char c)
{
	if (c == '|')
		return (1);
	if (ft_isspace(c))
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}
