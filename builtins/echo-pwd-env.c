/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-pwd-env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/16 12:12:44 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echon(char **args)
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

void	echo(char **args)
{
	int	i;

	if (!args[1])
		ft_printf("\n");
	else
	{
		if (!ft_strncmp(args[1], "-n", 3))
			echon(args);
		else
		{
			i = 1;
			while (args[i])
			{
				if (args[i + 1] == NULL)
					ft_printf("%s", args[i]);
				else
					ft_printf("%s ", args[i]);
				i++;
			}
			ft_printf("\n");
		}
	}
}

void	pwd(void)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
		exit(1);
	ft_printf("%s\n", cwd);
}

void	env(char **args, char **envp)
{
	int	i;

	if (args[1])
		ft_printf("env: too many arguments\n");
	else
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strchr(envp[i], '='))
				ft_printf("%s\n", envp[i]);
			i++;
		}
	}
}

//handle arguments?
void	exit_cmd(char **args)
{
	if (args[1])
		ft_printf("exit: too many arguments\n");
	else
	{
		ft_printf("exit\n");
		exit(0);
	}
}
