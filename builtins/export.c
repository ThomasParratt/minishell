/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/17 14:30:13 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_existing_name(char *existing, char **envp, int i)
{
	int	j;

	if (!existing)
		exit(1);
	j = 0;
	while (envp[i][j] != '=')
	{
		existing[j] = envp[i][j];
		j++;
	}
	existing[j] = '\0';
	return (existing);
}

static char	*env_exists(char *arg, char **envp)
{
	int		len;
	int		i;
	char	*existing;

	len = 0;
	while (arg[len] != '=' && arg[len] != '\0')
		len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], arg, len))
		{
			existing = malloc(sizeof(char) * len + 1);
			existing = get_existing_name(existing, envp, i);
			return (existing);
		}
		i++;
	}
	return (NULL);
}

static char	**unset_existing(char *arg, char **envp)
{
	char		**new_envp;
	char		*existing;

	existing = env_exists(arg, envp);
	if (existing)
	{
		new_envp = unset(existing, envp);
		free(existing);
		return (new_envp);
	}
	return (envp);
}

char	**export(char *arg, char **envp)
{
	char	**new_envp;
	int		i;

	envp = unset_existing(arg, envp);
	new_envp = malloc_envp(envp);
	if (!new_envp)
		exit(1);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(arg);
	i++;
	new_envp[i] = NULL;
	free_2d(envp);
	return (new_envp);
}

// in alphabetical order?
static void	print_declare(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	**export_cmd(char **args, char **envp)
{
	if (!args[1])
		print_declare(envp);
	else
		envp = export(args[1], envp);
	return (envp);
}
