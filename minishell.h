/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/07 14:21:44 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	**cmd1;
	char	*path1;
	char	**cmd2;
	char	*path2;
}				t_cmd;

char		*get_path(char **tokens, char **envp);
void		free_2d(char **tab);
void		print_2d(char **split);
char		*join_and_free(char *prompt, char *str);
int			contains_pipe(char *line_read);
extern void	rl_replace_line(const char *text, int clear_undo);
void		execute_pipe(t_cmd *cmds, char **argc);
void    	echo(char **args);
void    	pwd(void);
void		cd(char **args, char **envp);
void		env(char **envp);
void		exit_cmd(void);
char		**export(char *arg, char **envp);
char		**unset(char *arg, char **envp);
char		*ft_getenv(char **envp, char *str);

#endif
