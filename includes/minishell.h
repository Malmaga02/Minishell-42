/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:33:51 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/22 18:24:59 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include "builtin.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include <signal.h>

extern int				g_status_code;

typedef struct s_all	t_all;

typedef struct s_input
{
	char			*content;
	char			**args;
	int				token;
	int				merge;
	int				fd_in;
	int				fd_out;
	bool			prevent;
	struct s_input	*next;	
	struct s_input	*prev;
}	t_input;

typedef struct s_all
{
	t_list		*envp;
	t_input		*cmd_line;
	int			**pipes;
	int			std_fd_in;
	int			std_fd_out;
}	t_all;

// Free_exit_handling
void			free_parsing(t_parsing *parsing);
void			set_clear_all(t_all *all);
void			free_all(t_all *all);
void			close_all(t_all *all);

// Lst_input_handling
void			dll_input_addback(t_input **lst, t_input *new);
void			dll_input_addfront(t_input **lst, t_input *new);
void			dll_input_clear(t_input **lst);
t_input			*dll_input_last(t_input *lst);
t_input			*dll_input_new(char *content);
int				dll_input_size(t_input *lst);

#endif