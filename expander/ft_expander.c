/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 21:26:45 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 18:45:21 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

void	fill_expander(t_expand *pand)
{
	while (pand->input[pand->i] != '\0')
	{
		if (pand->input[pand->i] == '$')
			dollar_fill_expander(pand);
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
	line->pand->i_size = count_malloc(line->pand);
	if (line->pand->i_malloc == 1)
		ft_exit_with_error(line, "malloc error", 2);
}

static void	go_to_fill_expander(t_read *line, char *last_exit_code, char *argv)
{
	size_t	i;

	i = line->pand->i_size;
	initialize_pand(line->pand);
	line->pand->result = ft_calloc(i + 1, sizeof(char));
	if (!(line->pand->result))
		ft_exit_with_error(line, "malloc error", 2);
	line->pand->last_exit_code = last_exit_code;
	line->pand->argv = argv;
	line->pand->input = line->line;
	fill_expander(line->pand);
	if (line->pand->i_malloc == 1)
		ft_exit_with_error(line, "malloc error", 2);
	line->pand->result[i] = '\0';
}

char	*ft_expander(t_read *line, char *last_exit_code, char *argv)
{
	if (!line->line)
	{
		if (last_exit_code)
			free(last_exit_code);
		return (NULL);
	}
	go_to_count_malloc(line, last_exit_code, argv);
	go_to_fill_expander(line, last_exit_code, argv);
	free(line->line);
	free(line->pand->last_exit_code);
	line->pand->last_exit_code = NULL;
	return (line->pand->result);
}

