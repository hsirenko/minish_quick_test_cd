/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s.veselova <s.veselova@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:55:55 by s0nia             #+#    #+#             */
/*   Updated: 2024/03/31 15:32:30 by s.veselova       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1)
	{
		printf("No args allowed! Sowwy..\n");
		exit(1);
	}
	printf("welcome to..NANOSHELL\n\n\n");
	init_env(argc, argv, envp);
	while (1)
	{
		input = readline("nanoshell$ ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			execute_cmd(input, g_env);
		}
		free(input);
	}
	return (0);
}
