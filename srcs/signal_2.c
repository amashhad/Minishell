/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/03 19:42:10 by amashhad         ###   ########.fr       */
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
