/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/23 04:23:15 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint3(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	write(1, "\n", 1);
}

void	ft_signal3(int mod)
{
	(void)mod;
	signal(SIGINT, handle_sigint3);
	signal(SIGQUIT, handle_sigint3);
}

void	handel_sigint4(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig = 2;
	close(0);
}

void	ft_signal4(int mod)
{
	(void)mod;
	signal(SIGINT, handel_sigint4);
}
