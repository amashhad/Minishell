/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chg_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:14:34 by amashhad          #+#    #+#             */
/*   Updated: 2025/03/07 00:00:42 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_chng_pwd(t_read *line)
{
	ft_get_prompt(line);
	line->enviro = ft_srchrarr("PWD=", line->enviro, line->cwd);
	if (!line->enviro)
		ft_exit_with_error("Malloc Error");
	line->expo = ft_srchrarr("PWD=", line->expo, line->cwd);
	if (!line->enviro)
		ft_exit_with_error("Malloc Error");
}

static	void	ft_get_new_cwd(t_read *line, char *srch)
{
	static int	dir;
	int	i;

	i = -1;
	while (line->enviro[i] != NULL)
		if (ft_strnstr(line->enviro[++i], srch, ft_strlen(srch)))
			break;
	if (line->enviro[i] == NULL)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n", srch);
		return ;
	}
	dir = chdir(ft_strchr(line->enviro[i], '=') + 1);
	if (dir < 0)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n", srch);
		return ;
	}
	ft_chng_pwd(line);
}

static	void	ft_old_cwd(t_read *line)
{
	char	*old_pwd;

	old_pwd = ft_strjoin("OLD_PWD=", line->cwd);
	if (!old_pwd)
		ft_exit_with_error("Strjoin Error w/PWD");
	line->enviro = ft_srchrarr("OLD_PWD", line->enviro, old_pwd);
	if (!line->enviro || *line->expo == NULL)
		ft_exit_with_error("");
	line->expo = ft_srchrarr("OLD_PWD", line->expo, old_pwd);
	if (!line->expo || *line->expo == NULL)
		ft_exit_with_error("");
	free(old_pwd);
	ft_get_new_cwd(line, "HOME=");
}
static	void	ft_path(t_read *line)
{
	int	dir;
	char	*old_pwd;

	dir = chdir(line->tokens[1]);
	if (dir < 0)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n");
		return ;
	}
	old_pwd = ft_strjoin("OLD_PWD=", line->cwd);
	if (!old_pwd)
		ft_exit_with_error("strjoin Error w/PWD");
	line->enviro = ft_srchrarr("OLD_PWD=", line->enviro, old_pwd);
	if (!line->enviro || *line->enviro == NULL)
		ft_exit_with_error("srchrarr error");
	line->expo = ft_srchrarr("OLD_PWD=", line->enviro, old_pwd);
	if (!line->expo || *line->expo == NULL)
		ft_exit_with_error("srchrarr error");
	free(old_pwd);
	ft_chng_pwd(line);
}

void	ft_handle_cd(t_read *line)
{
	if (line->tokens[1] == NULL)
		ft_old_cwd(line);
	else if (ft_strncmp(line->tokens[1], "~", 1))
		ft_old_cwd(line);
	else if (ft_strncmp(line->tokens[1], "|", 1))
		ft_path(line);
	else
		return ;
}
