/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:00:06 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 15:43:11 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	initialize_pand(t_expand *pand)
{
	pand->i = 0;
	pand->i_result = 0;
	pand->i_size = 0;
	pand->count = 0;
	pand->j = 0;
	pand->count = 0;
	pand->k = 0;
	pand->i_malloc = 0;
	pand->last_exit_code = NULL;
	pand->string = NULL;
	pand->argv = NULL;
	pand->quoted = NULL;
	pand->input = NULL;
	pand->var_name = NULL;
	pand->var_value = NULL;
	pand->result = NULL;
	if (!pand->envment)
		pand->envment = NULL;
}

void	ft_free_expander(t_expand *pand)
{
	if (pand)
	{
		if (pand->result)
		{
			free(pand->result);
			pand->result = NULL;
		}
		if (pand->envment)
			ft_farray(pand->envment);
		if (pand->last_exit_code)
			free (pand->last_exit_code);
		if (pand->var_name)
			free (pand->var_name);
		if (pand->string)
			free (pand->string);
		if (pand->quoted)
			free (pand->quoted);
		if (pand->input)
			free (pand->input);
		free (pand);
	}
}

// void	go_to_check_error_arrow(t_read *line)
// {
// 	size_t	i;

// 	i = 0;
// 	while (line->line[i] != '\0')
// 	{
// 		if (line->line[i] == '>')
// 		{
// 			if (line->line[i + 1] == '<')
// 			{
// 				ft_putendl_fd("Syntax Error near token", 2);
// 				line->exit_status = 2;
// 				return ;
// 			}
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (line->line[i] != '\0')
// 	{
// 		if (line->line[i] == '<')
// 		{
// 			if (line->line[i + 1] == '>')
// 			{
// 				ft_putendl_fd("Syntax Error near token", 2);
// 				line->exit_status = 2;
// 				return ;
// 			}
// 		}
// 		i++;
// 	}
// }

// void	go_to_check_arrow_two(t_read *line)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (line->line[i] != '\0')
// 	{
// 		if (line->line[i] == '<')
// 			j++;
// 		if (line->line[i] == ' ')
// 			j = 0;
// 		if (j > 2)
// 		{
// 			ft_putendl_fd("Syntax Error near token", 2);
// 			line->exit_status = 2;
// 			return ;
// 		}
// 		i++;
// 	}
// }

// void	go_to_check_arrow(t_read *line)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (line->line[i] != '\0')
// 	{
// 		if (line->line[i] == '>')
// 			j++;
// 		if (line->line[i] == ' ')
// 			j = 0;
// 		if (j > 2)
// 		{
// 			ft_putendl_fd("Syntax Error near token", 2);
// 			line->exit_status = 2;
// 			return ;
// 		}
// 		i++;
// 	}
// 	go_to_check_arrow_two(line);
// 	go_to_check_error_arrow(line);
// }
