/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lotrapan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:24:46 by lotrapan          #+#    #+#             */
/*   Updated: 2024/07/24 15:40:56 by lotrapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_all	t_all;
typedef struct s_input	t_input;

/*------------------ECHO------------------*/
void					builtin_echo(char **av);
/*------------------ENV------------------*/
void					builtin_env(t_all *shell);
void					print_env(t_list *envp);
/*------------------EXIT------------------*/
int						builtin_exit(t_all *shell, char **av);
/*------------------PWD------------------*/
void					builtin_pwd(void);
/*------------------CD------------------*/
int						builtin_cd(t_all *shell, char **av);
/*------------------UNSET------------------*/
int						builtin_unset(char **av, t_list *envp);
/*------------------EXPORT------------------*/
int						builtin_export(t_all *shell, char **av);
void					export_err(char *str, int *error);
/*------------------EXPORT_UTILS------------------*/
int						equal_check(char *str);
int						doppelganger_check(t_list *envp, char *str, int len);
void					change_node_env(t_list **envp, char *key, int eq);
int						char_check(char *str, int *error);
void					print_export_quotes(char *str);
/*------------------EXEC_MAIN------------------*/
void					exec_main(t_all *shell);
void					exec_command(t_all *shell, t_input *cmd_line);
void					pipe_init(t_all *shell, t_input *current, int i);
int						count_pipe(t_input *cmd_line);
/*------------------EXEC_UTILS------------------*/
void					exec_builtin(t_all *shell, t_input *current);
bool					is_builtin(t_input *current);
int						count_commands(t_input *cmd_line);
t_all					*create_pipe(t_all *shell, int cmd_num);
void					finish_exec(t_all *shell);
void					handle_child(t_all *shell, t_input *cmd, int i);
/*------------------EXEC_FREE------------------*/
void					close_pipes(t_all *shell);
void					free_pipes(t_all *shell);
/*------------------REDIRECT------------------*/
int						handle_redirect(t_all *shell);
t_input					*find_cmd_in_block(t_input *block);
/*------------------REDIRECT_UTILS------------------*/
int						handle_input(char *path);
int						handle_output(char *path);
int						handle_append_output(char *path);
void					close_exec_fd(void);
/*------------------HEREDOC------------------*/
int						handle_heredoc(t_all *shell);
char					*open_file(char *file_name, int *fd);
void					heredoc_putendl_fd(char *s, int fd, t_all *shell);
/*------------------SIGNAL------------------*/
void					handle_signal_child(int signal);
void					handle_sigint(int signal);
void					handle_sigint_exec(int signal);
/*------------------ENVP_UTILS------------------*/
void					add_node_env(t_list **envp, char *str);
t_list					*change_env_variable(t_list *envp, char *var,
							char *new);
char					*find_word_in_env(t_list *envp, char *word);
t_list					*find_node_in_env(t_list *envp, char *word, int len);
/*------------------GENERAL_UTILS------------------*/
char					*get_path(t_all *shell, char *cmd);
char					**lst_to_mtx(t_list *envp);
bool					all_spaces(char *str);
int						ft_strcmp(const char *s1, const char *s2);
int						mtx_size(char **mtx);

int						dll_input_size(t_input *lst);
t_input					*dll_input_last(t_input *lst);
void					dll_input_addback(t_input **lst, t_input *new);
t_input					*dll_input_new(char *content);

#endif