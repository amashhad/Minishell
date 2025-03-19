/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:48:06 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/19 18:01:36 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	quoted(t_tok *token)
{
	int	k;
	char		c;

	k = token->index;
		if (token->input[token->i] == '"' || token->input[token->i] == '\'')
		{
			c = token->input[token->i];
			token->i++;
			while ((token->input[token->i] != c || (token->input[token->i] == c && token->input[token->i - 1] == '\\')) && token->input[token->i] != '\0')
				token->i++;
			if (token->input[token->i] != '\0')
				token->i++;
			while (k == token->index)
			{
				if (comper(token->input[token->i]))
					token->index++;
				if (token->input[token->i] != '\0')
					token->i++;
			}
		}
}
