/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirenko <hsirenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:16:58 by hsirenko          #+#    #+#             */
/*   Updated: 2024/04/06 20:50:35 by hsirenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"
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

typedef struct s_data
{
	char **pyp[10][2];
    int		**pipes;
    char	**env;
} t_data;

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



char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len_s1;
	char	*tab;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	tab = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!tab)
		return (NULL);
	while (s1[++i])
		tab[i] = s1[i];
	i = -1;
	while (s2[++i])
		tab[len_s1 + i] = s2[i];
	tab[len_s1 + i] = '\0';
	return (tab);
}

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

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
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












int	error_cd(char *str)
{
	ft_putstr_fd(ft_strjoin(str, " : No such file or dir\n"), STDERR_FILENO);
	return (1);
}


int	cd_prev_dir(t_data *data, int index)
{
	char	*prev_dir;

	prev_dir = get_env_var("OLDPWD", data);
	if (prev_dir == NULL)
	{
		free(prev_dir);
		ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	chdir(prev_dir);
	ft_putstr_fd(ft_strjoin(prev_dir, "\n"), data->pipes[index][1]);
	free(prev_dir);
	return (0);
}

// Mock data initialization function
void init_mock_data(t_data *data) {
    // Initialize environment variables
    data->env = (char **)malloc(2 * sizeof(char *));
    data->env[0] = ft_strjoin("OLDPWD=", "/path/to/previous/dir");
    data->env[1] = NULL; // Null-terminate the array

    // Initialize pipes (assuming index 0 is used)
    data->pipes = (int **)malloc(sizeof(int *));
    data->pipes[0] = (int *)malloc(2 * sizeof(int));
    // Initialize pipe ends or set to NULL if not used
}

int test_cd_prev_dir() {
    // Initialize mock data
    t_data data;
    init_mock_data(&data);

    // Call cd_prev_dir function
    int result = cd_prev_dir(&data, 0);

    // Print result
    if (result == 0) {
        printf("cd_prev_dir function executed successfully.\n");
    } else {
        printf("cd_prev_dir function failed.\n");
    }

    // Free allocated memory in mock data
    for (int i = 0; data.env[i] != NULL; i++) {
        free(data.env[i]);
    }
    free(data.env);
    // Free pipes if allocated

    return result;
}

int main()
{
    test_cd_prev_dir();
    return (0);
}


// int main()
// {
//     t_data *data;

//     data = malloc(sizeof(t_data));
//     if (data == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return 1;
//     }

//     char *test_dir = ft_strdup("/path/to/previous/dir");
//     char *oldpwd = ft_strdup("OLDPWD=/home/hsirenko/Documents/minishell_=/usr/bin/printenv");

//     data->pyp[0][1] = &test_dir;
//     data->pyp[0][0] = &oldpwd;

//     // Test case 1: When OLDPWD is set
//     cd_prev_dir(data, 0);

//     // Test case 2: When OLDPWD is NOT set
//     data->pyp[0][0] = NULL;
//     cd_prev_dir(data, 0);

//     free(test_dir);
//     free(oldpwd);
//     while (data->pyp[0][0] != NULL)
//     {
//         free(data->pyp[0][0]);
//         data->pyp[0][0] = NULL;
//     }
//     while (data->pyp[0][1] != NULL)
//     {
//         free(data->pyp[0][1]);
//         data->pyp[0][1] = NULL;
//     }
//     free(data);

//     return 0;
// }

// int main() {
//     // Test case 1: Call error_cd with a specific error message
//     printf("Test Case 1:\n");
//     error_cd("test_directory");

//     // Test case 2: Call error_cd with a different error message
//     printf("\nTest Case 2:\n");
//     error_cd("another_directory");

//     return 0;
// }