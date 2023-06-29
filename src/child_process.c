#include "pipex.h"

static void report_command(char *command)
{
	ft_printf("%s: command not found\n", command);
}

int put_valid_cmds(char *cmd, t_pipex *a, char ***args, char **path)
{
	int x;

	x = 0;
	*args = ft_split(cmd, ' ');
	if (!*args)
		error_func("Couldn't Malloc");
	*path = ft_strdup((*args)[0]);
	if (!access(*path, X_OK))
		return (1);
	while (a->paths[x])
	{
		if (*path)
			free(*path);
		*path = ft_strjoin(a->paths[x], (*args)[0]);
		if (!access(*path, X_OK))
			return (1);
		x++;
	}
	return (0);
}

void child_process(t_pipex *a, int i, char **envp)
{
	char **args;
	char *pathcmd;
	int flag;

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
	}
	else
	{
		report_command(a->cmds[i]);
		file_descriptors_manager(i, a);
	}
	clean_split(a->paths);
	clean_split(args);
	free(pathcmd);
	exit(EXIT_FAILURE);
}
