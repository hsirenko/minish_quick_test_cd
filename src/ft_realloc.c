/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:24:57 by s.veselova        #+#    #+#             */
/*   Updated: 2024/03/31 15:32:13 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*megamalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!(ptr))
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	min_size;

	if (!ptr)
		return (NULL);
	new_ptr = megamalloc(new_size);
	if (!(new_ptr))
	{
		free(ptr);
		return (NULL);
	}
	if (old_size < new_size)
		min_size = old_size;
	else
		min_size = new_size;
	ft_memcpy(new_ptr, ptr, min_size);
	free(ptr);
	return (new_ptr);
}

char	**realloc_g_env(int new_size)
{
	char	**new_genv;
	int		i;

	new_genv = (char **)megamalloc(sizeof(char *) * (new_size + 1));
	if (!new_genv)
	{
		printf("Fuuck! allocation error\n");
		return (NULL);
	}
	i = 0;
	while (i < new_size && g_env[i])
	{
		new_genv[i] = ft_strdup(g_env[i]);
		free(g_env[i]);
		i++;
	}
	free(g_env);
	return (new_genv);
}
