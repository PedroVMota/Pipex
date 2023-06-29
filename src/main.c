/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:49:38 by pedromota         #+#    #+#             */
/*   Updated: 2023/06/29 15:04:49 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_init(t_pipex *a, char **envp)
{
	int i;
	int *pid;

	i = -1;
	pid = malloc(sizeof(int) * (a->n_args));
	if (!pid)
		error_func("Malloc Error");
	while (++i < a->n_args)
	{
		if (pipe(a->fds->end) == -1)
			error_func("Pipe Error");
		if (i == 0 && a->is_heredoc)
			heredoc(a);
		a->pid = fork();
		pid[i] = a->pid;
		if (a->pid == -1)
			error_func("Fork Error");
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

int checkargs(char **params)
{
	int i;

	i = 0;
	while (params[i])
	{
		if (!params[i][0])
			return (0);
		i++;
	}
	return (1);
}

int main(int ac, char **av, char **en)
{
	set_modes(av, pipex(), ac);
	if (pipex()->n_args < 1)
		error_func("Not enough arguments");
	formatpath(en);
	pipex_init(pipex(), en);
	exec_exit(pipex());
}
