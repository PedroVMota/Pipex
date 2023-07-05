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

static void	cleanall(char **paths, char **args, char *str, int status)
{
	if (paths)
		clean_split(paths);
	if (args)
		clean_split(args);
	if (str)
		free(str);
	// close((pipex())->fds->end_point);
	// close((pipex())->fds->end[1]);
	// close((pipex())->fds->end[0]);
	// close((pipex())->fds->fd[0]);
	// close((pipex())->fds->fd[1]);
	perror("OOF");
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
	printf("NAO EXUCUTAR\n");
	return (1);
}

void	child_process(t_pipex *a, int i, char **envp)
{
	char	**args;
	char	*pathcmd;
	int		flag;
	int		status;

	args = NULL;
	pathcmd = NULL;
	status = 1;
	if (!access(a->cmds[i], X_OK))
	{
		pathcmd = ft_strdup(a->cmds[i]);
		args = ft_split(a->cmds[i], ' ');
		flag = 1;
	}
	else
		flag = put_valid_cmds(a->cmds[i], a, &args, &pathcmd);
	if (flag == 0)
	{
		ft_printf("%s\n", strerror(errno));
		file_descriptors_manager(i, a);
		cleanall(a->paths, args, pathcmd, status);
	}
	file_descriptors_manager(i, a);
	char *test[2] = {"lpo", NULL};
	status = execve(test[0], test, envp);
	fprintf(stderr, "status mano: %d\n", errno);
	perror(NULL);

	cleanall(a->paths, args, pathcmd, status);
}
