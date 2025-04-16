/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:35:06 by amashhad          #+#    #+#             */
/*   Updated: 2025/04/11 19:18:20 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	ft_free_tokenizer(t_tok *token)
{
	int	i;

	if (token)
	{
		if (token->tokens)
		{
			i = 0;
			while (token->tokens[i])
			{
				free(token->tokens[i]);
				i++;
			}
			free(token->tokens);
		}
		free (token);
	}
}
