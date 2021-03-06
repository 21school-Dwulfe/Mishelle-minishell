/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:56:30 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/24 23:45:24 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "structures.h"
# include "features.h"

/* * * PARSER * * */
/**
 * @brief Main parse function that replace special signs with tokens
 * 
 * @param str input line
 * @return int In case of success returns 0 else returns 1
 */
int			msh_parse(char **str);

/**
 * @brief Function in while loop checks 
 * str[i] if it is a special sign and returns it
 * 
 * @param str input string
 * @param i index of char
 * @return int enum code of special sign
 */
int			msh_check_special_signs(char *str, int *i);

/**
 * @brief Cut current redirect & change next type for recursion
 * 
 * @param dest - redirect file name for adding in redirect struct
 * @param src  - income string or previos tail
 * @param tail - tail after first redirect
 * @param c - next type of redirect from list of  < , > , << , >>
 * @return int 1 - requirement to use recursion
 */
int			msh_first_redirect(t_command *cmd, int *i, char *c);

/**
 * @brief Cuts redirects and saves in list of redirects
 * 
 * @return int In case of success returns 0 else returns -1
 */
void		msh_cut_redirects(t_command *cmd, int i, char *c, int *in);
int			msh_cut_redirects_cmd(void);
/* END PARSER */

/* COMMANDS */
void		msh_custom_exit(t_command *cmd);
int			msh_custom_pwd(t_command *cmd);
int			msh_custom_echo(t_command *cmd);
int			msh_custom_env(t_command *cmd);
int			msh_custom_cd(t_command *cmd);
int			msh_custom_export(t_command *cmd);
int			msh_custom_unset(t_command *cmd);
/* END COMMANDS */

/* * * UTILS  * * */
/**
 * @brief Function reallocates array of pointers on strings 
 * 
 * @param cmd Command
 */
void		msh_replace_null_arg(t_command *cmd);
/* END OF UTILS */

/* CONDITIONS */
int			msh_conditions_d_quotes_close(char *str, int *i);
int			msh_conditions_quotes_close(char *str, int *i);
int			msh_conditions_quotes(char *str, int *i);
int			msh_conditions_d_quotes(char *str, int *i);
int			msh_conditions_dollar_braces(char *str, int *i);
int			msh_conditions_semicolon(char *str, int *i);
int			msh_conditions_pipe(char *str, int *i);
int			msh_conditions_eof(char *str, int *i);
int			msh_validation_closest_chars(char *str, int *i);
int			msh_validation_double_amp(char *str, int *i);
int			msh_validation_double_pipe(char *str, int *i);
int			msh_conditions_wildcard(char *str, int *i);
int			msh_conditions_slash(char *str, int *i);
int			msh_conditions_d_pipe(char *str, int *i);
int			msh_conditions_d_amp(char *str, int *i);
int			msh_conditions_curl_braces(char *str, int *i);
int			msh_conditions_redirects(char *str, int *i);
int			msh_conditions_redirects(char *str, int *i);
/* End of conditions */

/* Signals */
void		msh_sigignore(void);
void		msh_sigint_handler(int sig_num);
void		msh_define_subshell_signals(char *shell_start, char *shell_current);
void		msh_child_sig(int sig);
/* End of signals */

/* Config */
void		msh_config(int argc, char **argv, char **env, int *regime);
/* End Config */

/* Input */
void		msh_stdin_regime(void);
/*End Input */

/* Specials */
void		msh_cut_set(char **src, char *set);
void		msh_cut_quotes(char **str, int i, int len);
void		msh_common_side_effect(char **str, int *i, int sp);
/* End Specials */

/* Tokens */
void		msh_widlcard_mutations(t_command *cmd, t_arg *tok, int *i);
void		msh_heredoc_input(char *path);
void		msh_convert_tilda(char **value, char *name);
void		msh_convert_to_redirect(t_command *cmd, char *value, int sp);
void		msh_wildcard(char *path, char **result);
char		*msh_token_wildcard_name(char *str, int *index);
char		*msh_token_redirect(char *str, int *index);
char		*msh_tokens_pseudo(int sp);
char		*msh_tokens_pseudo_dev(int sp);
char		*msh_token_tilda_name(char *str, int *i);
int			msh_conditions_tilda(char *str, int *i);
char		*msh_token_tilda_value(char *arg);
/* End Tokens */

/* Utils */
char		**msh_concat_insert_args(char **args, char **ar, int size);
int			msh_tok_pseudo_reader_dev(char *arg);
int			msh_tok_pseudo_reader(char *str);
char		*msh_tokens_pseudo(int sp);
/* End utils */

int			msh_evaluate_env_if_exist(char **args, char **env);
void		msh_cmd(char **line);
char		*msh_get_env_by_key(char **env, char *argument);
void		msh_struct_clear(void);
void		msh_save_error_code(int code);
int			msh_read_error_code(void);
int			msh_perror(char *cmd_name);
int			msh_error_bash(char *message, char *str, int code);
char		**msh_concat_args(char **cmd, int size);
char		*msh_concat_str(char *arg, int size, char *insertion);
int			msh_buildins(t_command *cmd, int reg);
void		msh_exchange_token_value(t_command *cmd, int index);
void		msh_pipex_two_step(t_command *cmd, char **env);
int			msh_executor(t_command *cmd, int *in_out_s, int *counter);
void		msh_pipex_recursion(t_command *cmd, char **env);
void		msh_pipex_loop(t_command *cmd, char **env);
void		msh_wait_pid(int pid);
char		**msh_create_env_var(char *new_var);
char		*msh_read_fd(int fd);
int			msh_d_amp_d_pipe(t_command *cmd);

/**
 * @brief change path to relative if it necessary
 * 
 * @param cmd_name 	command name
 * @param env 		envaroment variable array
 * @return char* return new allocated string else return NULL
 */
char		*msh_get_path(char *cmd_name, char **env);
char		**msh_copy_env(char **array);
t_command	*msh_create_command(char **dstr);
t_redirect	*msh_create_redirect(char *filepath, int specials);
t_arg		*msh_create_token(char *name, char *value, int order, int specials);
void		msh_push_redirect(t_redirect **current, char *value, t_specials sp);
int			msh_open(char *path, int type);
int			msh_export_invalid(char *arg);
int			msh_export_error(char *arg);
int			msh_multiple_iterator(int num, int *i, int sign);
void		msh_execution(t_command *cmd, char **env);
char		*msh_strncat(char *line, char *reall);
char		*msh_get_str_inside(char *str, char *set, int reg);
void		msh_add_command(t_command **cur_cmd, char **value);
int			msh_is_token(char *arg);
int			msh_validate_line(char *line);
char		*msh_dollar_error_case(char **args, char *tmp);
char		*msh_evaluate_env_arg(char *arg, char **env);
int			msh_unexpected_token_error(char *token_str, int token_len);
int			msh_pipes(t_command *cmd, int *fd_pipe);
/**
 * @brief 
 * 
 * @param env 
 * @param argument 
 * @return char* return pointer not additional alocated
 */
char		*msh_get_env_by_key(char **env, char *argument);
int			msh_env_exist(char **env, char *argument);
int			msh_modify_env_var(char **env, char *new_value);
int			msh_specify_token(int *length, char *str, int specials);
char		*msh_token_quotes(char *str, int *index);
char		*msh_token_d_quotes(char *str, int *index);
char		*msh_token_dollar(char *str, int *index);
char		*msh_generate_tokens(int specials, int num);
t_arg		*msh_get_token_value(t_command *cmd, char *token);
char		*msh_dollar(char *str, int *index);
char		*msh_dollar_braces(char *str, int *index);
char		*msh_token_curl_braces(char *str, int *index);
int			msh_validation_redirs(char *str, int *i);
void		msh_side_effects(char **str, int *i, int *specials);
int			msh_buildins_s(t_command *cmd);
void		msh_reflection_turn_on(void);
int			msh_redirects_fd(t_command *cmd);
int			msh_define_redirects(int *fd_arr, t_command *cmd);
int			msh_buildin_excutor(t_command *cmd);
/**
 * @brief Check cmd if it is one of buildin functions
 * 
 * @param cmd command
 * @return int if success returns index from buildin arraylist else return -1 
 * */
int			msh_is_build(char *cmd);
void		msh_evaluate_all_tokens(t_command *cmd);
int			msh_make_path_relative(t_command *cmd);
void		msh_specials_replace(char **str, char *insert, int *start, int end);
void		msh_func(t_command *cmd, int *fd_s, char **env, int *fd_pipe);
/**
 * @brief Cut's redirect signs, if they are clumped with filename or previos arg
 * j[0] = NULL	
 * j[1] = int of redirect < , > 
 * j[2] = index of another type of redirect if it exist in the string
 * j[3] = iterator for loop
 * @param i - current index of args
 * @param c - string with redirect
 */
void		msh_cut_recursion(t_command *cmd, int i, char *c);

/**
 * @brief check command name if it not a dir
 * 
 * @param cmd current command to execute
 * @return int 1 TRUE; 0 FALSE;
 */
int			msh_first_arg_validation(t_command *cmd);

/**
 * @brief 
 * 
 * @param arguments an array of arguments to look for in a variable environment
 * @param env variable environment
 * @return int returns index of var if true 0 if false
 */
int			msh_env_exist(char **env, char *argument);

/**
 * @brief 
 * 
 * @param arg 
 * @param size  - size of whole str with nulls
 * @param insertion - string which need to be inserted
 * @return char* 
 */
char		*msh_concat_str(char *arg, int size, char *insert);

/* GLOBALS */
void		msh_init_global_cmd(void);
t_redirect	*msh_last_redirect(t_command *cmd);
/*End GLOBALS */

t_command	*msh_last_cmd(void);
t_arg		*msh_last_token(void);
void		msh_add_token(t_command *cmd, t_arg *arg);
void		msh_side_effect(char **str, int *i, int *specials);
int			msh_conditions_dollar(char *str, int *i);
void		msh_specials_cut(char **str, int *i, int end);
char		*msh_get_prev_word(char *str, int length, char *set);
char		*msh_get_next_word(char *str, int length, char *set);
char		*msh_slash(char *str, int *index);
int			msh_preparings(t_command *cmd);
void		msh_input_call(char **str, int *i);

#endif
