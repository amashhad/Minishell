/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 23:00:51 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/20 00:00:02 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	fill_expander(t_expand *pand)
{
	while (pand->input[pand->i] != '\0')
	{
		if (pand->input[pand->i] == '>' || pand->input[pand->i] == '<')
			fill_arrow(pand);
		if (pand->input[pand->i] == '$')
			dollar_fill_expander(pand);
		else if (pand->input[pand->i] == '"')
			fill_double_quoted(pand);
		else if (pand->input[pand->i] == '\'')
		{
			single_quoted(pand);
			pand->i++;
			fill_value_expander(pand, pand->quoted);
			free (pand->quoted);
			pand->quoted = NULL;
		}
		else
		{
			pand->result[pand->i_result] = pand->input[pand->i];
			pand->i_result++;
			pand->i++;
		}
	}
}

static void	go_to_count_malloc(t_read *line, char *last_exit_code, char *argv)
{
	initialize_pand(line->pand);
	line->pand->last_exit_code = last_exit_code;
	line->pand->argv = argv;
	line->pand->input = line->line;
	line->pand->envment = ft_cpyarr(line->enviro);
	line->pand->pand_error = 0;
	if (!line->pand->envment)
	{
		free(last_exit_code);
		ft_exit_with_error(line, "Malloc Error in pand->envment", "pand", 2);
	}
	line->pand->i_size = count_malloc(line->pand);
	ft_farray(line->pand->envment);
	line->pand->envment = NULL;
	if (line->pand->i_malloc == 1)
		ft_exit_with_error(line, "malloc error", "pand", 2);
	if (line->pand->pand_error == 1)
		line->i_error = 1;
}

static void	go_to_fill_expander(t_read *line, char *last_exit_code, char *argv)
{
	size_t	i;

	i = line->pand->i_size;
	initialize_pand(line->pand);
	line->pand->result = ft_calloc(i + 1, sizeof(char));
	if (!(line->pand->result))
		ft_exit_with_error(line, "malloc error", "pand", 2);
	line->pand->last_exit_code = last_exit_code;
	line->pand->argv = argv;
	line->pand->input = line->line;
	line->pand->envment = ft_cpyarr(line->enviro);
	fill_expander(line->pand);
	if (line->pand->i_malloc == 1)
		ft_exit_with_error(line, "malloc error", "pand", 2);
	line->pand->result[i] = '\0';
	ft_farray(line->pand->envment);
	line->pand->envment = NULL;
	if (line->pand->pand_error == 1)
		line->i_error = 1;
}

char	*ft_expander(t_read *line, char *last_exit_code, char *argv)
{
	line->exit_status = 0;
	if (!line->line)
	{
		if (last_exit_code)
			free(last_exit_code);
		return (NULL);
	}
	go_to_check_arrow(line);
	if (line->exit_status == 2)
	{
		free(last_exit_code);
		return (line->line);
	}
	go_to_count_malloc(line, last_exit_code, argv);
	go_to_fill_expander(line, last_exit_code, argv);
	free(line->pand->last_exit_code);
	line->pand->last_exit_code = NULL;
	return (line->pand->result);
}
