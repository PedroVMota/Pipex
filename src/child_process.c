#include "pipex.h"

int put_valid_cmds(char *cmd, t_pipex *a, char ***args, char **path)
{
	int x;

	x = 0;

	if (!cmd)
		return 1;
	*args = ft_split(cmd, ' ');
	*path = ft_strdup((*args)[0]);
	if (!access(*path, F_OK))
		return (1);
	while (a->paths[x])
	{
		if (*path)
			free(*path);
		*path = ft_strjoin(a->paths[x], (*args)[0]);
		if (!access(*path, F_OK))
			return (1);
		x++;
	}
	return (0);
}

void child_process(t_pipex *a, int i, char **envp)
{
	char **args;
	char *pathcmd;

	printf("Cheking the Command %s%s%s\n", GRN, a->cmds[i], RESET);
	file_descriptors_manager(i, a);
	if (access(a->cmds[i], X_OK | F_OK) == -1)
	{
		put_valid_cmds(a->cmds[i], a, &args, &pathcmd);
		clean_split(args);
		free(pathcmd);
		error_func("Command not found");
	}
	else
	{
		printf("a->cmds[i] = %s\n", a->cmds[i]);
		args = ft_split(a->cmds[i], ' ');
		pathcmd = ft_strdup(a->cmds[i]);
		execve(pathcmd, args, envp);
	}
	if (!access(pathcmd, X_OK))
		execve(pathcmd, args, envp);
	clean_split(args);
	free(pathcmd);
	error_func("Command not found");
}
