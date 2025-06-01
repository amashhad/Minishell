/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_compare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:43:02 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/30 16:55:09 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

int	comper_expander(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	if (c == ' ')
		return (1);
	if (c == '\0')
		return (1);
	if (c == '$')
		return (1);
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	string_expander(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

void	double_quoted(t_expand *pand)
{
	if (pand->input[pand->i] == '"')
	{
		//pand->j = pand->i;
		pand->i++;
		pand->count++;
		//pand->k++;
		while (pand->input[pand->i] != '"'
			&& pand->input[pand->i] != '\0')
		{
			if (pand->input[pand->i] == '$')
				dollar_malloc_expander(pand);
			pand->count++;
			pand->i++;
			//pand->k++;
		}
		if (pand->input[pand->i] == '\0')
		{
			pand->count--;
			pand->i--;
		}
		//pand->k++;
		// pand->quoted = get_string_expander(pand);
		// pand->string = NULL;
	}
}

void	fill_double_quoted(t_expand *pand)
{
	if (pand->input[pand->i] == '"')
	{
		pand->result[pand->i_result] = pand->input[pand->i];
		pand->i_result++;
		pand->i++;
		while (pand->input[pand->i] != '"'
			&& pand->input[pand->i] != '\0')
		{
			if (pand->input[pand->i] == '$')
				dollar_fill_expander(pand);
			else
			{
				pand->result[pand->i_result] = pand->input[pand->i];
				pand->i_result++;
				pand->i++;
			}
		}
		if (pand->input[pand->i] == '\0')
		{
			pand->pand_error = 2;
			pand->i--;
		}
		pand->result[pand->i_result] = pand->input[pand->i];
		pand->i_result++;
		pand->i++;
	}
}

char	*token_without_quoted(char *str)
{
	char	*s;
	char	c;
	int		i;
	int		k;

	i = 0;
	k = 0;
	s = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!s)
		return (NULL);
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i] != '\0')
			{
				s[k] = str[i];
				i++;
				k++;
			}
			i++;
		}
		else
		{
			s[k] = str[i];
			i++;
			k++;
		}
	}
	s[k] = '\0';
	return (s);
}

void	loop_remove(t_read *line)
{
	int	i;

	i = 0;
	while (line->token->tokens[i])
	{
		line->token->tokens[i] = token_without_quoted(line->token->tokens[i]);
		i++;
	}
}