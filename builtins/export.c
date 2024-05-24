/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/24 12:11:08 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_existing_name(char *existing, t_data *data, int i)
{
	int	j;

	if (!existing)
		exit(1);
	j = 0;
	while (data->envp[i][j] != '=' && data->envp[i][j] != '\0')
	{
		existing[j] = data->envp[i][j];
		j++;
	}
	existing[j] = '\0';
	return (existing);
}

static char	*env_exists(char *arg, t_data *data)
{
	int		len;
	int		i;
	char	*existing;

	len = 0;
	while (arg[len] != '=' && arg[len] != '\0')
		len++;
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], arg, len))
		{
			existing = malloc(sizeof(char) * len + 1);
			if (!existing)
				malloc_failure();
			existing = get_existing_name(existing, data, i);
			return (existing);
		}
		i++;
	}
	return (NULL);
}

static void	unset_existing(char *arg, t_data *data)
{
	char		*existing;

	existing = env_exists(arg, data);
	if (existing)
	{
		unset(existing, data);
		free(existing);
	}
}

void	export(char *arg, t_data *data)
{
	char	**new_envp;
	int		i;

	unset_existing(arg, data);
	new_envp = malloc_envp(data->envp);
	if (!new_envp)
		malloc_failure();
	i = 0;
	while (data->envp[i])
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		if (!new_envp[i])
			malloc_failure();
		i++;
	}
	new_envp[i] = ft_strdup(arg);
	if (!new_envp[i])
		malloc_failure();
	i++;
	new_envp[i] = NULL;
	free_2d(data->envp);
	data->envp = new_envp;
}

// in alphabetical order?
static void	print_declare(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		ft_printf("declare -x %s\n", data->envp[i]);
		i++;
	}
}

void	export_cmd(char **args, t_data *data)
{
	int	i;

	if (!args[1])
		print_declare(data);
	else
	{
		i = 1;
		while (args[i])
		{
			export(args[i], data);
			i++;
		}
	}
}
