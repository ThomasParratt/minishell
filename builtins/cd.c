/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/08 10:25:53 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//res should not have a slash at the end
static char	*get_new_pwd(char *pwd, int slash_count)
{
	int		i;
	int		num;
	int		count;
	char	*res;

	i = 0;
	num = 0;
	while (pwd[i] && num != slash_count)
	{
		if (pwd[i] == '/')
			num++;
		i++;
	}
	res = malloc(sizeof(char) * i + 1);
	count = i;
	i = 0;
	while (pwd[i] && i < count - 1)
	{
		res[i] = pwd[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	get_slash_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;

	while (str[i])
	{
		if (str[i] == '/')
			count++;
		i++;
	}
	return (count);
}

char	**cd(char **args, char **envp)
{
	char	*pwd;
	int		slash_count;
	char	*new_pwd;

	if (args[1] && ft_strncmp(args[1], "..", 2) == 0)
	{
		pwd = ft_getenv(envp, "PWD");
		slash_count = get_slash_count(pwd);
		new_pwd = get_new_pwd(pwd, slash_count);
		pwd = ft_strjoin("OLDPWD=", pwd);
		envp = export(ft_strjoin("PWD=", new_pwd), envp);
		envp = export(pwd, envp);
		if (chdir(new_pwd) != 0)
		{
			ft_printf("Error changing directory\n");
			exit(1);
		}
	}
	return (envp);
}
