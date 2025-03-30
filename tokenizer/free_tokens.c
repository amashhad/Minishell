/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:35:06 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/30 21:35:42 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	ft_free_tokenizer(t_tok *token, int error)
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
		}
		free(token->tokens);
		free (token);
	}
	if (error == 0)
	{
		printf("The Malloc Not Located\n");
		exit (0);
	}
}
