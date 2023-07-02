/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:04:49 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/02 19:05:30 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_split(char **var)
{
	int	i;

	i = 0;
	if (!var || !*var)
		return ;
	while (var[i] != NULL)
		free(var[i++]);
	free(var);
}

int	count_doubles(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	error_func(char *msg)
{
	clean_split(pipex()->paths);
	close(pipex()->fds->end_point);
	if (pipex()->fds->fd[0] != -1)
		close(pipex()->fds->fd[0]);
	if (pipex()->fds->fd[1] != -1)
		close(pipex()->fds->fd[1]);
	if (pipex()->fds->dups[0] != -1)
		close(pipex()->fds->dups[0]);
	if (pipex()->fds->dups[1] != -1)
		close(pipex()->fds->dups[1]);
	if (msg)
		ft_printf("%s\n", msg);
	ft_printf("./pipex infile cmd1 cmd2 outfile\n");
	exit(EXIT_FAILURE);
}

/*
** exec_exit - frees memory allocated for a 2D array of strings
** @a: pointer to the pipex struct
*/
void	exec_exit(t_pipex *a)
{
	clean_split(a->paths);
	exit(0);
}