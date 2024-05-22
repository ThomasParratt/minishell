/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/22 12:49:24 by tparratt         ###   ########.fr       */
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

static int	check_args(char **args, t_data *data)
{
	if (!args[1])
		return (1);
	if (chdir(args[1]) == -1)
	{
		print_error_message(args, data);
		data->err_num = 1;
		return (1);
	}
	return (0);
}

void	cd(char **args, t_data *data)
{
	char	*old_pwd_path;
	char	*new_pwd;
	char	*old_pwd;
	char	*new_pwd_path;

	old_pwd_path = getcwd(NULL, 0);
	if (!old_pwd_path)
		exit(1);
	if (check_args(args, data) == 1)
		return ;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_path);
	if (!old_pwd)
		exit(1);
	new_pwd_path = getcwd(NULL, 0);
	if (!new_pwd_path)
		exit(1);
	new_pwd = ft_strjoin("PWD=", new_pwd_path);
	if (!new_pwd)
		exit(1);
	export(old_pwd, data);
	export(new_pwd, data);
	free_strings(old_pwd, new_pwd, old_pwd_path, new_pwd_path);
}
