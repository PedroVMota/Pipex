/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:45:11 by pvital-m          #+#    #+#             */
/*   Updated: 2023/06/27 21:16:25 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void path_setup(char **path)
{
	char *tmp;
	int i;

	i = 0;
	tmp = NULL;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			error_func("Could not malloc:");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
}

static int permission_check(char *name, char *cmd)
{
	if (!access(cmd, F_OK) && access(cmd, X_OK) == -1)
	{
		printf("%s%s%s: Permission denied\n", RED, name, RESET);
		return -1;
	}
	else if (!access(cmd, F_OK) && !access(cmd, X_OK))
	{
		printf("%s%s%s: Command not found\n", RED, name, RESET);
		return -1;
	}
	else
	{
		printf("%s%s%s: No such file or directory\n", RED, name, RESET);
		return -1;
	}
	return 1;
}

void check_commands(t_pipex *a)
{
	int i;
	char **args;
	char *cmd_path;

	i = -1;
	args = NULL;
	cmd_path = NULL;
	while (++i < a->n_args)
	{
		if (access(a->cmds[i], F_OK) == 0)
		{
			if (access(a->cmds[i], X_OK) == -1)
				printf("%s%s%s: Permission denied\n", RED, a->cmds[i], RESET);
			else
				break;
		}
		else
		{
			put_valid_cmds(a->cmds[i], a, &args, &cmd_path);
			if (permission_check(a->cmds[i], cmd_path))
				break;
		}
		if (args)
			clean_split(args);
		if (cmd_path)
			free(cmd_path);
	}
}

void formatpath(char **__enviroment)
{
	char *temp;

	while (ft_strncmp(*__enviroment, "PATH=", 5))
		__enviroment++;
	temp = ft_substr(*__enviroment, 5, ft_strlen(*__enviroment));
	(pipex())->paths = ft_split(temp, ':');
	if (!pipex()->paths)
		error_func("Unable to Set the Paths\n");
	path_setup(pipex()->paths);
	check_commands((pipex()));
	free(temp);
}
