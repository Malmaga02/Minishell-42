/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalmari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:30:16 by mgalmari          #+#    #+#             */
/*   Updated: 2024/07/26 11:30:21 by mgalmari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

# define SYNTAX_ERROR "syntax error near unexpected token\n"

typedef struct s_all	t_all;

typedef struct s_input	t_input;

typedef enum e_quotes
{
	STAY,
	MERGE_PREV,
	MERGE_NEXT,
	MERGE_BOTH,
}	t_quotes;

typedef enum e_token
{
	VOID,
	WORDS,
	ARG,
	CMD,
	FILE_W,
	EOF_DEL,
	DOLLAR_SIGN,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	HEREDOC,
	D_RED_OUTPUT,
	D_QUOTE,
	S_QUOTE,
	OPERATORS,
	REDIRECTS,
	QUOTES,
}	t_token;

typedef struct s_parsing
{
	char	*input;
	char	**mtx_from_input;
	int		*arr_token;
	int		size;
	int		need_free;
}	t_parsing;

// --- Parsing --- //

// -Expansion- //
//Expand_with_quotes
int			check_dollar_sign(char *str);
void		new_content_copy(char *new_content, char *content,
				char *env, int len);
char		*get_content_with_quotes(char *content, char *env);

//Expand
void		*expand_env(char *content, t_all all_info);
void		*expand_env_with_quotes(char *content, t_all all_info);
t_all		expand_dollar_sign(t_all all_info);

//Get_env
int			get_len_word(char *str, int index);
int			get_index_special_char(char *str, char c);
char		*get_expansion(t_list *envp, char *name_env);
char		*get_name_env(char *str);
char		*get_env(char *str, t_all all_info);

//Handling_env
int			find_len_env(t_list *envp, char *name_env);
char		*find_expansion_env(t_list *envp, char *name_env);
int			len_escaped_char(char *env);
char		*handle_escaped_char(char *env);

// -Get_info- //
// Get_all_info
t_parsing	*parse_input(t_parsing *parsing);
t_input		*create_list_from_input(t_parsing *parsing);
t_list		*create_list_from_envp(char **envp);
t_all		get_all_info(t_all all_info, char *line, char **envp);

// Get_args_mtx
char		**handle_args_red(t_input *cmdline, char **args,
				int if_cmd_before_red);
char		**get_args_cmds(t_input *cmdline);
char		**get_args_redirects(t_input *cmdline, t_input *head);
t_input		*get_args_mtx(t_input *cmd_line);

// Get_arr_token
int			*handle_redirect_word_token(int *arr_token, int size);
int			handle_exp_with_heredoc(int *arr_token, int index, int token);
int			first_token_check(int *arr_token, int size);
int			*analyse_words_token(int *arr_token, int size);
int			*get_arr_token(char **mtx, int size);

// Get_input_complete
t_all		reorganize_cmdline(char *line, t_all all_info);
t_all		get_final_input(char *line, t_all all_info);
t_all		get_input_complete(t_all all_info, char *line, char **envp);

// Get_merge_flag
int			check_cases_for_merge_with_quotes(char current, char before);
t_input		*switch_merge_flag(t_input *cmd_line, int token_nbr,
				int which_merge);
t_input		*handle_merge_flag(char *input, t_input *cmd_line,
				int token_nbr, int i);
t_input		*check_if_need_merge(t_parsing *parsing, t_input *cmd_line);

// Get_merged_line
char		*get_content_merged(char **mtx, int *i, int *merge_arr, int size);
char		*handle_merge_next(char	**mtx_cmdline, int *merge_arr, int *index);
char		*get_new_input(char	**mtx_cmdline, int *merge_arr, int size);
char		*get_merged_line(t_input *cmd_line, int *merge_arr);

// Get_mtx_input
int			count_words(char *s);
int			word_len(char *s);
char		**new_string(char **mtx, char *s);
char		**get_mtx_from_input(t_parsing *parsing);

// Get_void_cmd
int			check_if_redirect_before(t_input *head, int current);
t_input		*organize_token(t_input *cmdline);
t_input		*set_void_token(t_input *cmdline);
t_all		check_if_void_cmd(t_all all_info);

// -Handlers- //
// Handling_args_mtx
int			find_if_cmd_before_red(t_input *head, t_input *cmdline);
int			count_args_redirect(t_input *cmdline, int if_cmd_before_red);
int			count_args(t_input *cmdline, int token, int if_cmd_before_red);
char		**complete_args(t_input *cmdline, int flag, char **args, int index);

// Handling_char
int			char_type(char c);
int			handle_quotes(char *s);
int			handle_operators(char *s);
int			handle_dollar_signs(char *s);
int			handle_not_spaces(char *s);

// Handling_merge_flag
int			check_if_need_reorganize_cmdline(t_input *cmdline);
int			find_merge_flag_quote(char *input, int i);
int			find_merge_flag_dollar_sign(char *input, int i);
int			find_which_merge_flag(char *input, int i, int token);

// Handling_merged_line
int			count_merge_next(int *merge_arr, int i, int size);
char		*delete_empty_env(char	*mtx_cmdline);
int			*get_merge_arr(t_input *cmd_line, int *merge_arr, int size);
int			*organize_merge_arr(int *arr, int size);
int			*find_index(int index, int *merge_arr, int size);

// Handling_mtx_and_lists
char		**parsing_list_in_mtx(t_input *cmd_line);

// Handling_quotes_as_word_token
t_all		assign_token_as_words_token(t_all all_info, int token);

// Handling_token
int			get_word_token(int token);
int			find_token(char *str);
int			find_token_type(int token);
int			check_which_operator(int token);
int			handle_syntax_error_operators(int *arr_token, int i, int size);

// Trim_quotes
char		*trim_quotes(char *content);
char		*trim_dollar_signs(char *content);
char		*trim(char *content, int token);
t_all		handle_trim_special_char(t_all all_info, int token);

#endif
