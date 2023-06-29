/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:46:58 by pedromota         #+#    #+#             */
/*   Updated: 2023/06/29 11:23:46 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	uploadstartdata(void)
{
	(pipex())->fds->dups[0] = -1;
	(pipex())->fds->dups[1] = -1;
}

static void	set_files(t_pipex *a)
{
	if (a->is_heredoc)
		(pipex())->fds->fd[1] = open(a->files[1], O_CREAT | O_RDWR | O_APPEND,
			0644);
	else
	{
		a->fds->fd[0] = open(a->files[0], O_RDONLY);
		if (a->fds->fd[0] == -1)
			printf("There is no such file %s%s%s\n", RED ,a->files[0], RESET);
		(pipex())->fds->fd[1] = open(a->files[1], O_CREAT | O_RDWR | O_TRUNC,
			0644);
	}
}

void	set_modes(char **av, t_pipex *a, int ac)
{
	a->files[1] = av[ac - 1];
	if (ft_strncmp(av[1], "here_doc", 9) != 0)
	{
		a->is_heredoc = 0;
		a->cmds = &av[2];
		a->files[0] = av[1];
		a->n_args = ac - 2;
	}
	else
	{
		a->cmds = &av[3];
		a->is_heredoc = 1;
		a->delimeter = av[2];
		a->n_args = ac - 3;
	}
	uploadstartdata();
	set_files(a);
}
