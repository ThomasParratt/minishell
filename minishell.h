/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/04/29 14:45:21 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	**cmd1;
	char	*path1;
	char	**cmd2;
	char	*path2;
}				t_cmd;

char	*get_path(char **tokens);
void	free_split(char **tab);
void	print_split(char **split);
char	*join_and_free(char *prompt, char *str);
int		contains_pipe(char *line_read);

#endif
