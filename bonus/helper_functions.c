/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:04:49 by pedromota         #+#    #+#             */
/*   Updated: 2023/06/24 16:42:33 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** clean_split - frees memory allocated for a 2D array of strings
** @var: pointer to the 2D array of strings
** @length: length of the 2D array of strings
*/
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

/*
** count_doubles - counts the number of strings in a 2D array of strings
** @s: pointer to the 2D array of strings
** Return: the number of strings in the 2D array of strings
*/
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

/*
** error_func - frees memory allocated for a 2D array of strings,
	closes file descriptors and exits with failure
** @msg: error message to be printed
*/
void	error_func(char *msg)
{
	clean_split(pipex()->paths);
	close(pipex()->fds->end_point);
	if (pipex()->fds->dups[0] != -1)
		close(pipex()->fds->dups[0]);
	if (pipex()->fds->dups[1] != -1)
		close(pipex()->fds->dups[1]);
	if (msg)
		ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/*
** exec_exit - frees memory allocated for a 2D array of strings
** @a: pointer to the pipex struct
*/
void	exec_exit(t_pipex *a)
{
	clean_split(a->paths);
}
