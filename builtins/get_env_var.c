/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:18:23 by hsirenko          #+#    #+#             */
/*   Updated: 2024/04/06 18:17:33 by hsirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while ((unsigned char)*s != uc && *s != '\0')
	{
		s++;
	}
	if ((unsigned char)*s == uc)
	{
		return ((char *)s);
	}
	else
	{
		return (NULL);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	diff;

	diff = 0;
	while (!diff && n-- && (*s1 || *s2))
		diff = (unsigned char) *s1++ - (unsigned char) *s2++;
	return (diff);
}

size_t	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	while (*str++)
	{
		n++;
	}
	return (n);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == NULL)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_env_var(char *var_name, t_data *data)
{
	char	*env_var;
	char	*val;
	int		i;

	env_var = NULL;
	val = NULL;
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			env_var = ft_strchr(data->env[i], '=');
			if (env_var)
			{
				val = ft_strdup(env_var + 1);
				return (val);
			}
		}
		i++;
	}
	return (NULL);
}

// int main()
// {
// 	t_data *data;

// 	data = (t_data *)malloc(sizeof(t_data));
// 	if (data == NULL)
// 	{
// 		fprintf(stderr, "Failed to allocate memory for t_data\n");
// 		return 1;
// 	}

// 	char *env[] = {
// 			"HOME=/path/to/home",
// 			NULL
// 	};
// 	data->env = env;
// 	char *var_name = "HOME";

// 	char *result = get_env_var(var_name, data);
// 	if (result != NULL)
// 	{
// 		printf("result: %s\n", result);
// 		free(result);
// 	}
// 	else
// 		printf("Environment variable %s not found\n", var_name);
// 	free(data);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	unsigned char	uc;

// 	uc = (unsigned char)c;
// 	while ((unsigned char)*s != uc && *s != '\0')
// 	{
// 		s++;
// 	}
// 	if ((unsigned char)*s == uc)
// 	{
// 		return ((char *)s);
// 	}
// 	else
// 	{
// 		return (NULL);
// 	}
// }

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	int	diff;

// 	diff = 0;
// 	while (!diff && n-- && (*s1 || *s2))
// 		diff = (unsigned char) *s1++ - (unsigned char) *s2++;
// 	return (diff);
// }

// size_t	ft_strlen(const char *str)
// {
// 	int	n;

// 	n = 0;
// 	while (*str++)
// 	{
// 		n++;
// 	}
// 	return (n);
// }

// char	*ft_strdup(const char *src)
// {
// 	char	*dest;
// 	size_t	i;

// 	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
// 	if (dest == NULL)
// 		return (0);
// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }