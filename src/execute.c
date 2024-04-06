/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s0nia <s0nia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:44:19 by s0nia             #+#    #+#             */
/*   Updated: 2024/03/31 19:17:45 by s0nia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_path_helper(char **split, char *cmd, char *tmp, int i)
{
	char	*path;

	i = 0;
	while (split[i])
	{
		tmp = ft_strjoin(split[i], "/");
		if (!tmp)
		{
			ft_free(split);
			ft_error();
		}
		path = ft_strjoin(tmp, cmd);
		if (!path)
		{
			free(tmp);
			ft_free(split);
			ft_error();
		}
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (0);
}

static char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**split;
	char	*tmp;
	char	*path;

	i = 0;
	tmp = NULL;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	split = ft_split(envp[i] + 5, ':');
	if (!split)
		ft_error();
	path = get_path_helper(split, cmd, tmp, i);
	if (!path)
	{
		ft_free(split);
		free(tmp);
		return (NULL);
	}
	else
		return (path);
	ft_free(split);
	return (0);
}

static char	*prepare_cmd(char *argv, char ***cmd, char **envp)
{
	char	*path;

	*cmd = ft_split(argv, ' ');
	path = NULL;
	if (!*cmd)
		ft_error();
	if (!ft_strchr((*cmd)[0], '/')
		&& ((*cmd)[0][0] != '.' && (*cmd)[0][1] != '/'))
		path = get_path((*cmd)[0], envp);
	else
		path = (*cmd)[0];
	if (!path)
	{
		ft_free(*cmd);
		ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
		ft_putendl_fd(argv, 2);
		return (NULL);
	}
	return (path);
}

static void	execute_helper(char *path, char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmd, envp) == -1)
		{
			perror("execve fail");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("Fork fail");
}

void	execute_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (is_builtin(cmd))
	{
		ft_free(cmd);
		return ;
	}
	else
	{
		cmd = NULL;
		path = prepare_cmd(argv, &cmd, envp);
		if (!path)
			return ;
		execute_helper(path, cmd, envp);
		if (path != cmd[0])
			free(path);
		ft_free(cmd);
	}
}
