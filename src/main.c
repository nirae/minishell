/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 01:02:06 by ndubouil          #+#    #+#             */
/*   Updated: 2018/10/01 18:32:18 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signal(int signal)
{
	if (signal == SIGINT)
		exit(0);
	//printf("coucou\n");
}

/*
**	Return the complete path of a file name or exit if malloc failed
*/

static char	*get_complete_path(char *parent, char *name)
{
	char	*tmp;
	char	*result;

	if (parent[ft_strlen(parent) - 1] == '/')
	{
		if (!(tmp = ft_strdup(parent)))
			exit(0);
	}
	else
	{
		if (!(tmp = ft_strjoin(parent, "/")))
			exit(0);
	}
	if (!(result = ft_strjoin(tmp, name)))
		exit(0);
	ft_strdel(&tmp);
	return (result);
}

int		main(int ac, char **av, char **env)
{
	pid_t	father;
	char	*line;
	char	**command;
	char	**env_path;
	struct stat st;

	(void)ac;
	(void)av;
	while (666)
	{
		ft_printf("tape ta commande connard > ");
		signal(SIGINT, catch_signal);
		get_next_line(0, &line);
		if (ft_strcmp(line, "exit") == 0)
		{
			ft_printf("c'est ca degage\n");
			exit(0);
		}
		// recupere la commande
		command = ft_strsplit(line, ' ');
		// recupere le path
		//env_path = ft_strsplit(const char *s, char c);
		int i = 0;
		while (env[i])
		{
			char **path = ft_strsplit(env[i], '=');
			if (ft_strcmp(path[0], "PATH") == 0)
				env_path = ft_strsplit(path[1], ':');
			i++;
		}
		i = -1;
		while (env_path[++i])
		{

			if ((lstat(get_complete_path(env_path[i], command[0]), &st)) < 0)
				continue;
			father = fork();
			if (father == 0)
				execve(get_complete_path(env_path[i], command[0]), command, env);
			else if (father < 0)
				ft_printf("fail\n");
			else if (father > 0)
				wait(&father);
		}
		/*if (ft_strcmp(line, "exit") == 0)
		{
			ft_printf("c'est ca degage\n");
			exit(0);
		}*/
		/*father = fork();
		if (father == 0)
			execve(line, av, env);
		else if (father < 0)
			ft_printf("fail\n");
		else if (father > 0)
			wait(&father);*/
		//ft_printf("tiens ton resultat de merde : %s\n", line);
		ft_strdel(&line);
	}
	/*	father = fork();
		if (father > 0)
		{
			printf(">>>");
			wait(NULL);
			while (1);
			printf("PERE\n");
		}
		if (father == 0)
		{
			execve(av[1], &av[1], NULL);
		}
	*/
	return (0);
}
