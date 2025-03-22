/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 06:07:49 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 06:40:41 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

#include "../srcs/minishell.h"
#include "../libft/libft.h"

void	builtin(t_read *line);
void	ft_handle_cd(t_read *line);
void	ft_handle_echo(t_read *line);
void	ft_handle_export(t_read *line);
void	ft_handle_unset(t_read *line);

#endif
