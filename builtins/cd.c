/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/10 16:16:14 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cd(char **args, char **envp)
{
	char	*old_pwd_path;
	char	*new_pwd;
	char	*old_pwd;
	char	*new_pwd_path;

	if (chdir(args[1]) == -1)
		exit(1);
	old_pwd_path = ft_getenv(envp, "PWD");
	if (!old_pwd_path)
		exit(1);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_path);
	if (!old_pwd)
		exit(1);
	new_pwd_path = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", new_pwd_path);
	if (!new_pwd)
		exit(1);
	envp = export(old_pwd, envp);
	envp = export(new_pwd, envp);
	free(old_pwd);
	free(new_pwd);
	free(old_pwd_path);
	free(new_pwd_path);
	return (envp);
}
