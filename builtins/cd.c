/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/21 14:49:35 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_strings(char *str1, char *str2, char *str3, char *str4)
{
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

static int	check_args(char **args)
{
	if (!args[1])
		return (1);
	if (chdir(args[1]) == -1)
	{
		print_error_message(args);
		return (1);
	}
	return (0);
}

char	**cd(char **args, char **envp)
{
	char	*old_pwd_path;
	char	*new_pwd;
	char	*old_pwd;
	char	*new_pwd_path;

	if (check_args(args) == 1)
		return (envp);
	old_pwd_path = ft_getenv(envp, "PWD");
	if (!old_pwd_path)
		exit(1);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_path);
	if (!old_pwd)
		exit(1);
	new_pwd_path = getcwd(NULL, 0);
	if (!new_pwd_path)
		exit(1);
	new_pwd = ft_strjoin("PWD=", new_pwd_path);
	if (!new_pwd)
		exit(1);
	envp = export(old_pwd, envp);
	envp = export(new_pwd, envp);
	free_strings(old_pwd, new_pwd, old_pwd_path, new_pwd_path);
	return (envp);
}
