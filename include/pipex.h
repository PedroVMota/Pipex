/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvital-m <pvital-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:40:10 by pedromota         #+#    #+#             */
/*   Updated: 2023/07/02 19:21:58 by pvital-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "ft_colors.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include "libft.h"
# include "limits.h"
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_fds
{
	int		input;
	int		output;
	int		fd[2];
	int		end[2];
	int		dups[2];
	int		end_point;
}			t_fds;

typedef struct s_pipex
{
	t_fds	*fds;
	pid_t	pid;
	int		n_args;
	char	**paths;
	int		is_heredoc;
	char	*delimeter;
	char	**cmds;
	char	*files[2];
}			t_pipex;
// parsing

void		file_descriptors_manager(int command_selector, t_pipex *a);
t_pipex		*pipex(void);
void		formatpath(char **__enviroment);
void		clean_split(char **var);
void		error_func(char *msg);
void		copy_double_pointer(char **dest, char **src);
void		uploadstartdata(void);
void		exec_exit(t_pipex *a);
void		file_description_cleaner(int i, t_pipex *a);
void		set_modes(char **av, t_pipex *a, int ac);
void		child_process(t_pipex *a, int i, char **envp);
void		heredoc(t_pipex *a);
void		waitall(pid_t *all, int loop, int options);
void		command_checker(void);
#endif