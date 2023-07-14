/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:45:11 by pvital-m          #+#    #+#             */
/*   Updated: 2023/07/02 18:01:21 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	path_setup(char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			error_func("Could not malloc:");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
}

void	formatpath(char **__enviroment)
{
	char	*temp;

	while (ft_strncmp(*__enviroment, "PATH=", 5))
		__enviroment++;
	temp = ft_substr(*__enviroment, 5, ft_strlen(*__enviroment));
	(pipex())->paths = ft_split(temp, ':');
	if (!pipex()->paths)
		error_func("Unable to Set the Paths\n");
	path_setup(pipex()->paths);
	free(temp);
}
