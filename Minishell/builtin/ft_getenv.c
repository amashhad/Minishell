/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:15:20 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/16 20:31:37 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

char	*ft_getenv(t_read *line, char *env)
{
	char	*ret;

	ret = ft_fetcharr(line->enviro, env);
	return (ret);
}
