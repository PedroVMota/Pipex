/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 01:46:08 by pedromota         #+#    #+#             */
/*   Updated: 2023/06/29 10:49:30 by pvital-m         ###   ########.fr       */
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
void waitall(pid_t *all, int loop, int options)
{
	int i;

	i = 0;
	while (i < loop)
		waitpid(all[i++], NULL, options);
}



static int check_elements(char *input, char *target)
{
	int target_len;
	int input_len;

	target_len = ft_strlen(target);
	input_len = ft_strlen(input) - 1;

	printf("input: %s\n", input);
	printf("target: %s\n", target);
	printf("input_len: %d\n", input_len);
	printf("target_len: %d\n", target_len);
	if (ft_strncmp(input, target, target_len) == 0 && input_len == target_len)
		return 1;
	return 0;
}

void heredoc(t_pipex *a)
{
	char *text;
	int bytes_read;
	int here_doc[2];

	text = NULL;
	if (pipe(here_doc) == -1)
		error_func("Pipe Error:");
	a->fds->fd[0] = here_doc[0];
	bytes_read = 1;
	while (bytes_read > -1)
	{
		write(1, "heredoc > ", 10);
		text = get_next_line(0);
		if (check_elements(text, a->delimeter))
			break;
		write(here_doc[1], text, ft_strlen(text));
		free(text);
	}
	close(here_doc[1]);
}