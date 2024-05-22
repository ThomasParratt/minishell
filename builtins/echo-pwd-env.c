/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-pwd-env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/22 12:05:54 by tparratt         ###   ########.fr       */
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

void	env(char **args, t_data *data)
{
	int	i;

	if (args[1])
		ft_printf("minishell: env: too many arguments\n");
	else
	{
		i = 0;
		while (data->envp[i])
		{
			if (ft_strchr(data->envp[i], '='))
				ft_printf("%s\n", data->envp[i]);
			i++;
		}
	}
}

void	exit_cmd(char **args, t_data *data)
{
	int	i;
	int	num;

	ft_printf("exit\n");
	if (args[1])
	{
		i = 0;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				ft_printf("minishell: exit: %s: numeric argument required\n", args[1]);
				exit(255);
			}
			i++;
		}
		num = ft_atoi(args[1]);
		exit(num);
	}
	else
	{
		ft_printf("errno = %d\n", data->err_num); // this won't work
		exit(data->err_num);
	}
}
