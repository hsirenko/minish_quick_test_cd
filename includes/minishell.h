/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:54:17 by s0nia             #+#    #+#             */
/*   Updated: 2024/04/06 20:26:23 by hsirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	//char	***tokens;
	int		**pipes;
    char        **pyp[10][2];
	char	**env;
	//int		pipe_num;
}	t_data;

extern char	**g_env;

/* src/mini_utils.c */
void	ft_error(void);
void	ft_exit(void);
int		is_builtin(char	**command);
int		ft_strcmp(char *s1, char *s2);

/* src/env_handler.c */
int		ft_arraylen(char **array);
void	init_env(int ac, char **av, char **envp);
int		find_env_index(char *env_var);
void	ft_env(void);
void	add_to_env(char	*str);

/* src/execute.c */
void	execute_cmd(char *argv, char **envp);

/* src/export.c */
int		ft_export(char **arr);

/* src/ft_realloc.c */
char	**realloc_g_env(int new_size);
void	*megamalloc(size_t size);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

/* src/cleanup_utils.c */

void	cleanup(char **cmd, char *path);
void	ft_free(char **array);

/* builtins */
int		error_cd(char *str);
char	*get_env_var(char *var_name, t_data *data);

#endif