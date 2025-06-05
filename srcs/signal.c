/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/06/05 15:56:04 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_sig != 2)
	{
		g_sig = 1;
		write(1, "\n", 1);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(int mod)
{
	(void)mod;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	ft_signal2(int mod)
{
	(void)mod;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(int mode)
{
	if (mode == 1)
		ft_signal(1);
	if (mode == 2)
		ft_signal2(2);
	if (mode == 3)
		ft_signal3(3);
	if (mode == 4)
		ft_signal4(4);
}
