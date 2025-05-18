/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhamdan <alhamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:34:54 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/16 20:05:25 by alhamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 1;
}
void	handle_sigint3(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	write(1, "\n", 1);
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
void	ft_signal3(int mod)
{
	(void)mod;
	signal(SIGINT, handle_sigint3);
	signal(SIGQUIT, handle_sigint3);
}
void	setup_signals(int mode)
{
	if (mode == 1)
		ft_signal(1);
	if (mode == 2)
		ft_signal2(2);
	if (mode == 3)
		ft_signal3(3);
}
