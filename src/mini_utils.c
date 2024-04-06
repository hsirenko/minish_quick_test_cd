/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:24:09 by s0nia             #+#    #+#             */
/*   Updated: 2024/03/31 16:27:06 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

void	ft_error(void)
{
	perror("Error");
	return ;
}

void	ft_exit(void)
{
	ft_free(g_env);
	write(1, "\n", 1);
	exit(0);
}

int	is_builtin(char	**command)
{
	if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(command + 1));
	else if (ft_strcmp(command[0], "env") == 0)
	{
		ft_env();
		return (1);
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (!s1[i] && !s2[i])
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}
