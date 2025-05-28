/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amashhad <amashhad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:14:34 by amashhad          #+#    #+#             */
/*   Updated: 2025/05/28 21:40:11 by amashhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

static	void	ft_chng_pwd(t_read *line)
{
	char	*srch;

	ft_get_prompt(line);
	srch = ft_strjoin("PWD=", line->cwd);
	if (check_name_of_key(line->expo, "PWD"))
		add_rplc(line, "PWD", srch);
	free(srch);
}

static	void	ft_get_new_cwd(t_read *line, char *srch)
{
	int	dir;
	int	i;

	i = 0;
	dir = 0;
	while (line->enviro[i] != NULL)
	{
		if (ft_strnstr(line->enviro[i], srch, ft_strlen(srch)))
			break ;
		i++;
	}
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

	old_pwd = ft_strjoin("OLDPWD=", line->cwd);
	if (!old_pwd)
		ft_exit_with_error(line, "Strjoin Error w/PWD", "NULL", 1);
	line->enviro = ft_srchrarr("OLDPWD", line->enviro, old_pwd);
	if (!line->enviro || *line->expo == NULL)
		ft_exit_with_error(line, "old CWD err", "NULL", 1);
	line->expo = ft_srchrarr("OLDPWD", line->expo, old_pwd);
	if (!line->expo || *line->expo == NULL)
		ft_exit_with_error(line, "old CWD err", "NULL", 1);
	free(old_pwd);
	ft_get_new_cwd(line, "HOME=");
}

static	void	ft_path(t_read *line, char **cmd)
{
	int		dir;
	char	*old_pwd;

	dir = chdir(cmd[1]);
	if (dir < 0)
	{
		ft_printf("Minishell: cd: %s: No such file or directory\n", cmd[1]);
		return ;
	}
	old_pwd = ft_strjoin("OLDPWD=", line->cwd);
	if (!old_pwd)
		ft_exit_with_error(line, "strjoin Error w/PWD", "NULL", 1);
	line->enviro = ft_srchrarr("OLDPWD=", line->enviro, old_pwd);
	if (!line->enviro || *line->enviro == NULL)
		ft_exit_with_error(line, "srchrarr error", "NULL", 1);
	line->expo = ft_srchrarr("OLDPWD=", line->expo, old_pwd);
	if (!line->expo || *line->expo == NULL)
		ft_exit_with_error(line, "srchrarr error", "NULL", 1);
	free(old_pwd);
	ft_chng_pwd(line);
}

void	ft_handle_cd(t_read *line, char **cmd)
{
	if (ft_fetcharr(cmd, "|"))
		return ;
	if (cmd[1] == NULL || ft_strcmp("~", cmd[1]) == 0)
		ft_old_cwd(line);
	else
		ft_path(line, cmd);
}
