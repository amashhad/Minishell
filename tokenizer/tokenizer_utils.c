/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:37:16 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/03 19:49:07 by alhamdan         ###   ########.fr       */
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
	if (ft_isspace(c))
		return (1);
	if (c == '\0')
		return (1);
	if (c == '$')
		return (1);
	return (0);
}

void	greater_tokenizer(t_tok *token)
{
	while (token->input[token->i] == '>' || token->input[token->i] == '<')
	{
		if (token->input[token->i] == token->input[token->i + 1])
		{
			token->i++;
			token->index++;
		}
		else
			token->index++;
		token->i++;
	}
}

void	pipe_tokenizer(t_tok *token)
{
	if (token->input[token->i] == '|')
	{
		token->i++;
		token->index++;
	}
}

void	dollar_tokenizer(t_tok *token)
{
	if (token->input[token->i] == '$')
	{
		token->i++;
		token->index++;
	}
}

void	string_tokenizer(t_tok *token)
{
	while (!(comper(token->input[token->i])))
	{
		if ((token->input[token->i] == '"'
				|| token->input[token->i] == '\'')
			&& token->input[token->i - 1] != '\\')
		{
			token->c = token->input[token->i];
			token->i++;
			while ((token->input[token->i] != token->c
					|| (token->input[token->i] == token->c
						&& token->input[token->i - 1] == '\\'))
				&& token->input[token->i] != '\0')
				token->i++;
		}
		if (token->input[token->i] == '\0')
		{
			token->i--;
			token->error_token = 2;
		}
		if (comper(token->input[token->i + 1]))
			token->index++;
		token->i++;
	}
}
