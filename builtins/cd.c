/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/07 14:22:13 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reset_pwd(char *pwd, char *new_pwd, char **envp)
{
	unset(pwd, envp);
	export(new_pwd, envp);
}

static char	*get_new_pwd(char *pwd, int slash_count)
{
	int		i;
	int		num;
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
	i = 0;
	num = 0;
	while (pwd[i] && num != slash_count)
	{
		if (pwd[i] == '/')
			num++;
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

void	cd(char **args, char **envp)
{
	char	*pwd;
	int		slash_count;
	char	*new_pwd;

	if (args[1] && ft_strncmp(args[1], "..", 2) == 0)
	{
		pwd = ft_getenv(envp, "PWD");
		if (!pwd)
			exit(1);
		slash_count = get_slash_count(pwd);
		new_pwd = get_new_pwd(pwd, slash_count);
		chdir(new_pwd);
		reset_pwd(pwd, new_pwd, envp);
		free(new_pwd);
	}
}
