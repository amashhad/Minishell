/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:18:51 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/22 08:52:12 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	comper(char c)
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
	return (0);
}

void	fill_token(t_tok *token)
{
	if (token->index > token->k)
		{
			token->tokens[token->k] = malloc((token->i - token->count + 1) * sizeof(char));
			if (!token->tokens[token->k])
			{
				ft_free(token);
				exit(1);
			}
			token->j = 0;
			while (token->count < token->i)
			{
				token->tokens[token->k][token->j] = token->input[token->count];
				token->count++;
				token->j++;
			}
			token->tokens[token->k][token->j] = '\0';
		}
}

void	piipe(t_tok *token)
{
	while (token->input[token->i] == '|')
		{
			token->i++;
			token->index++;
		}
}

void	fill_tokens(t_tok *token)
{
	while (token->input[token->i] != '\0')
	{
		while (token->input[token->i] == ' ' || token->input[token->i] == '\t')
			token->i++;
		token->k = token->index;
		token->count = token->i;
		quoted(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		string(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		piipe(token);
		fill_token(token);
		token->k = token->index;
		token->count = token->i;
		greater(token);
		fill_token(token);
	}
}
