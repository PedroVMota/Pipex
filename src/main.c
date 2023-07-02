/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:49:38 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/02 18:00:18 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	manage_here_forking(int i, int *pid, t_pipex *a)
{
	if (i == 0 && a->is_heredoc)
		heredoc(a);
	a->pid = fork();
	pid[i] = a->pid;
	if (a->pid == -1)
		error_func("Fork Error");
}

void	pipex_init(t_pipex *a, char **envp)
{
	int	i;
	int	*pid;

	i = -1;
	pid = malloc(sizeof(int) * (a->n_args));
	if (!pid)
		error_func("Malloc Error");
	while (++i < a->n_args)
	{
		if (pipe(a->fds->end) == -1)
			error_func("Pipe Error");
		manage_here_forking(i, pid, a);
		if (a->pid == 0)
		{
			free(pid);
			child_process(a, i, envp);
		}
		file_description_cleaner(i, a);
	}
	waitall(pid, a->n_args, 0);
	free(pid);
}

int	main(int ac, char **av, char **en)
{
	if (ac - 1 < 4)
		error_func("Not enough arguments");
	set_modes(av, pipex(), ac);
	formatpath(en);
	if (!(pipex())->paths)
		error_func("Error Parsing the PATH variable");
	pipex_init(pipex(), en);
	exec_exit(pipex());
}
