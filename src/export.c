/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:57:41 by s.veselova        #+#    #+#             */
/*   Updated: 2024/03/31 11:43:15 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_export(char *str)
{
	char	*equals_pos;

	if (str == NULL)
		return (0);
	equals_pos = ft_strchr(str, '=');
	if (equals_pos == str)
		return (0);
	return (equals_pos != NULL);
}

int	ft_export(char **arr)
{
	int	i;

	i = 0;
	if (arr[0] == NULL)
	{
		ft_env();
		return (1);
	}
	while (arr[i] != NULL)
	{
		if (is_valid_export(arr[i]))
			add_to_env(arr[i]);
		i++;
	}
	return (1);
}
