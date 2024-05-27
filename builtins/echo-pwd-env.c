/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-pwd-env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/27 16:54:08 by tparratt         ###   ########.fr       */
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
				if (args[i + 1] == NULL || ft_strlen(args[i]) == 0)
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
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(errno);
	ft_printf("%s\n", cwd);
	free(cwd);
}

void	env(char **args, t_data *data)
{
	int	i;

	if (args[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		data->err_num = 1;
	}
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
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(255);
			}
			i++;
		}
		num = ft_atoi(args[1]);
		exit(num);
	}
	else
		exit(data->err_num);
}
