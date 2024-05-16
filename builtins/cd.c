/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/16 14:00:03 by tparratt         ###   ########.fr       */
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

//need to check invalid args
char	**cd(char **args, char **envp)
{
	char	*old_pwd_path;
	char	*new_pwd;
	char	*old_pwd;
	char	*new_pwd_path;

	if (!args[1])
		return (envp);
	/*if (ft_strncmp("../", args[1], 3) != 0 || ft_strncmp("..", args[1], 3) != 0 || ft_strncmp("/", args[1], 1) != 0)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", args[1]);
		return (envp);
	}*/
	if (chdir(args[1]) == -1)
		exit(1);
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
