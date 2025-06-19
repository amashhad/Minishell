/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_compare.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:43:02 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/20 00:25:10 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_expander.h"

static void	quotes_loop(t_expand *pand)
{
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
}

void	fill_double_quoted(t_expand *pand)
{
	int	mark;

	mark = 0;
	if (pand->input[pand->i] == '"')
	{
		pand->result[pand->i_result] = pand->input[pand->i];
		pand->i_result++;
		pand->i++;
		quotes_loop(pand);
		if (pand->input[pand->i] == '\0')
		{
			pand->result[pand->i_result] = pand->input[pand->i];
			pand->pand_error = 2;
			pand->i--;
			mark = 1;
		}
		if (mark == 0)
			pand->result[pand->i_result] = pand->input[pand->i];
		pand->i_result++;
		pand->i++;
	}
}

static void	quote_chk_loop(char *s, char *str, char c, int k)
{
	int	i;

	i = 0;
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
}

char	*token_without_quoted(char *str)
{
	char	*s;
	char	c;
	int		i;
	int		k;

	i = 0;
	k = 0;
	c = '\0';
	s = NULL;
	if (!str)
		return (NULL);
	s = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	if (!s)
	{
		perror("Calloc");
		return (NULL);
	}
	quote_chk_loop(s, str, c, k);
	return (s);
}
