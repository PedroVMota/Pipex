/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 04:06:24 by pvital-m          #+#    #+#             */
/*   Updated: 2023/07/01 18:19:18 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*pipex(void)
{
	static t_pipex	container;
	static t_fds	file_descriptors;

	container.fds = &file_descriptors;
	return (&container);
}

void	file_descriptors_manager(int command_selector, t_pipex *a)
{
	if (command_selector == 0)
		a->fds->dups[0] = dup2(a->fds->fd[0], STDIN_FILENO);
	else
		a->fds->dups[0] = dup2(a->fds->end_point, STDIN_FILENO);
	if (command_selector == a->n_args - 1)
		a->fds->dups[1] = dup2(a->fds->fd[1], STDOUT_FILENO);
	else
		a->fds->dups[1] = dup2(a->fds->end[1], STDOUT_FILENO);
	close(a->fds->end[0]);
	close(a->fds->end[1]);
	close(a->fds->fd[0]);
	close(a->fds->fd[1]);
}

void	file_description_cleaner(int i, t_pipex *a)
{
	close(a->fds->end[1]);
	if (i > 0)
		close(a->fds->end_point);
	else
		close(a->fds->fd[0]);
	if (i == a->n_args - 1)
	{
		close(a->fds->end[0]);
		close(a->fds->fd[1]);
	}
	a->fds->end_point = a->fds->end[0];
}
