/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 15:43:57 by pvital-m          #+#    #+#             */
/*   Updated: 2023/07/05 22:21:18 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	cleanall(char **paths, char **args, char *str)
{
	if (paths)
		clean_split(paths);
	if (args)
		clean_split(args);
	if (str)
		free(str);
	close((pipex())->fds->end_point);
	close((pipex())->fds->end[1]);
	close((pipex())->fds->end[0]);
	close((pipex())->fds->fd[0]);
	close((pipex())->fds->fd[1]);
	exit(errno);
}

int	put_valid_cmds(char *cmd, t_pipex *a, char ***args, char **path)
{
	int	x;

	x = 0;
	if (cmd[0] == '\0')
		return (0);
	*args = ft_split(cmd, ' ');
	if (!*args)
		error_func("Couldn't Malloc");
	*path = ft_strdup((*args)[0]);
	if (!access(*path, X_OK | F_OK))
		return (1);
	while (a->paths[x])
	{
		if (*path)
			free(*path);
		*path = ft_strjoin(a->paths[x], (*args)[0]);
		if (!access(*path, X_OK | F_OK))
			return (1);
		x++;
	}
	return (0);
}

void	child_process(t_pipex *a, int i, char **envp)
{
	char	**args;
	char	*pathcmd;
	int		flag;

	flag = 0;
	args = NULL;
	pathcmd = NULL;
	if (!access(a->cmds[i], X_OK))
	{
		pathcmd = ft_strdup(a->cmds[i]);
		args = ft_split(a->cmds[i], ' ');
		flag = 1;
	}
	else
		flag = put_valid_cmds(a->cmds[i], a, &args, &pathcmd);
	if (flag)
	{
		file_descriptors_manager(i, a);
		execve(pathcmd, args, envp);
		cleanall(a->paths, args, pathcmd);
	}
	cleanall(a->paths, args, pathcmd);
}
