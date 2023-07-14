/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:46:08 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/14 20:33:18 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	waitall(pid_t *all, int loop, int options)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < loop)
		waitpid(all[i++], &status, options);
	free(all);
	return (status);
}

static int	check_elements(char *input, char *target)
{
	int	target_len;
	int	input_len;

	target_len = ft_strlen(target);
	input_len = ft_strlen(input) - 1;
	if (ft_strncmp(input, target, target_len) == 0 && input_len == target_len)
		return (1);
	return (0);
}

void	heredoc(t_pipex *a)
{
	char	*text;
	int		bytes_read;
	int		here_doc[2];

	text = NULL;
	if (pipe(here_doc) == -1)
		error_func("Pipe Error:");
	a->fds->fd[0] = here_doc[0];
	bytes_read = 1;
	while (bytes_read > -1)
	{
		write(1, "heredoc > ", 10);
		text = get_next_line(0);
		if (!text)
		{
			free(text);
			continue ;
		}
		if (check_elements(text, a->delimeter))
			break ;
		write(here_doc[1], text, ft_strlen(text));
		free(text);
	}
	close(here_doc[1]);
}
