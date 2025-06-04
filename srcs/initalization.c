/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 08:51:48 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/04 22:37:10 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initalization_struct_pand(t_read *line)
{
	line->pand = malloc(sizeof(t_expand));
	if (!line->pand)
		exit (0);
	line->pand->i = 0;
	line->pand->i_result = 0;
	line->pand->i_size = 0;
	line->pand->count = 0;
	line->pand->j = 0;
	line->pand->count = 0;
	line->pand->k = 0;
	line->pand->i_malloc = 0;
	line->pand->pand_error = 0;
	line->pand->last_exit_code = NULL;
	line->pand->string = NULL;
	line->pand->argv = NULL;
	line->pand->quoted = NULL;
	line->pand->input = NULL;
	line->pand->var_name = NULL;
	line->pand->var_value = NULL;
	line->pand->result = NULL;
	line->pand->envment = NULL;
}

void	initalization_struct_tok(t_read *line)
{
	line->token = malloc(sizeof(t_tok));
	if (!line->token)
		exit (0);
	line->token->i = 0;
	line->token->index = 0;
	line->token->j = 0;
	line->token->count = 0;
	line->token->k = 0;
	line->token->error_token = 1;
	line->token->c = '\0';
	line->token->input = NULL;
	line->token->tokens = NULL;
}
void	line_malloc_init(t_read *line, char **envp)
{
	if (!envp || !*envp)
	{
		ft_putendl_fd("Enviro err: no ENV variable", 2);
		exit(1);
	}
	line->enviro = ft_cpyarr(envp);
	if (!line->enviro)
	{
		ft_putendl_fd("Enviro err: no memory for allocation", 2);
		exit (1);
	}
	line->expo = ft_cpyarr(line->enviro);
	if (!line->expo)
	{
		ft_putendl_fd("Expo err: no Memory for allocation", 2);
		ft_farray(line->enviro);
		exit (1);
	}
}

void	initalization(t_read *line, char **envp)
{
	initalization_struct_pand(line);
	initalization_struct_tok(line);
	ft_bzero(line->heredocs, sizeof(line->heredocs));
	line_malloc_init(line, envp);
	line->old_fd = 0;
	line->line = NULL;
	line->prompt = NULL;
	line->tokens = NULL;
	line->heredoc_dst = NULL;
	line->cwd = NULL;
	line->piper = NULL;
	line->heredoc_dst = NULL;
	line->exit_status = 0;
	line->piper_len = 0;
	line->i_error = 0;
}
