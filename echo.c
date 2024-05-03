/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/03 16:28:20 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (args[i + 1] == NULL)
			ft_printf("%s", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
}

void	cd(char **args)
{
	char	*pwd;
	int		i;
	int		count;
	int		num;
	char	*new_pwd;

	if (args[1][0] == '.' && args[1][1] == '.' && !args[1][2])
	{
		pwd = getenv("PWD");
		if (!pwd)
			exit(1);
		i = 0;
		count = 0;
		while (pwd[i])
		{
			if (pwd[i] == '/')
				count++;
			i++;
		}
		i = 0;
		num = 0;
		while (pwd[i] && num != count)
		{
			if (pwd[i] == '/')
				num++;
			i++;
		}
		i = 0;
		num = 0;
		new_pwd = malloc(sizeof(char) * i + 1);
		while (pwd[i] && num != count)
		{
			if (pwd[i] == '/')
				num++;
			new_pwd[i] = pwd[i];
			i++;
		}
		new_pwd[i] = '\0';
		chdir(new_pwd);
		//need to reset the value of PWD by entering the envp 2d array
	}
}

void	pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd command failure");
		exit(1);
	}
	ft_printf("%s\n", cwd);
}
