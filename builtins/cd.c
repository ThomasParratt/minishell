/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/06 09:31:05 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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