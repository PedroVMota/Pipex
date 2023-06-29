/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromota <pedromota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:46:08 by pedromota         #+#    #+#             */
/*   Updated: 2023/06/27 16:58:16 by pedromota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Wait for all child processes to finish.
 *
 * @param all Array of child process IDs.
 * @param loop Number of child processes.
 * @param options Options for waitpid function.

 */
void	waitall(pid_t *all, int loop, int options)
{
	int	i;

	i = 0;
	while (i < loop)
		waitpid(all[i++], NULL, options);
}

void	heredoc(t_pipex *a)
{
	char	*text;
	size_t	bytes_read;
	int		here_doc[2];

	text = NULL;
	if (pipe(here_doc))
		error_func("Pipe Error:");
	a->fds->fd[0] = here_doc[0];
	bytes_read = 1;
	while (bytes_read > (size_t)-1)
	{
		write(1, "pipe> ", 6);
		text = get_next_line(0);
		bytes_read = ft_strlen(text) - 1;
		if (ft_strncmp(text, a->delimeter, ft_strlen(a->delimeter)) == 0
			&& bytes_read == ft_strlen(a->delimeter))
		{
			free(text);
			break ;
		}
		write(here_doc[1], text, ft_strlen(text));
		free(text);
	}
	close(here_doc[1]);
}
