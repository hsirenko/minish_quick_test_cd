/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:57:56 by s.veselova        #+#    #+#             */
/*   Updated: 2024/03/31 15:35:15 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_arraylen(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		j++;
		i++;
	}
	return (j);
}

void	init_env(int ac, char **av, char **envp)
{
	int		i;

	(void)ac;
	(void)av;
	g_env = (char **)ft_calloc(ft_arraylen(envp) + 1, sizeof(char *));
	if (g_env == NULL)
		ft_exit();
	i = 0;
	while (envp[i])
	{
		g_env[i] = ft_strdup(envp[i]);
		if (!(g_env[i]))
			ft_exit();
		i++;
	}
}

int	find_env_index(char *env_var)
{
	int		i;
	char	*equals_pos;
	size_t	key_len;

	i = 0;
	if (!env_var)
		return (-1);
	equals_pos = ft_strchr(env_var, '=');
	if (!equals_pos)
		return (-1);
	key_len = equals_pos - env_var;
	while (g_env[i] != NULL)
	{
		if (ft_strncmp(g_env[i], env_var, key_len) == 0
			&& g_env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		printf("%s\n", g_env[i]);
		i++;
	}
	printf("\ncustom env\n");
}

void	add_to_env(char	*str)
{
	int	i;
	int	env_len;

	i = find_env_index(str);
	if (i >= 0)
	{
		free(g_env[i]);
		g_env[i] = ft_strdup(str);
	}
	else
	{
		env_len = ft_arraylen(g_env);
		g_env = realloc_g_env(env_len + 2);
		g_env[env_len] = ft_strdup(str);
		g_env[env_len + 1] = NULL;
	}
}
