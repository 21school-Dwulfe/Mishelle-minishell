#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"
#include "features.h"

int			msh_parse(char **str);
int			msh_help_parse_redirect(t_command *cmd, char *str, int *length, char *c);
void		msh_add_to_struct(char **result);
void		msh_push_command(t_command **cur_cmd, char **value);
void		msh_custom_exit(t_command *cmd);
int			msh_custom_pwd(t_command *cmd);
int			msh_custom_echo(t_command *cmd);
int			msh_custom_env(t_command *cmd);
int			msh_custom_cd(t_command *cmd);
int			msh_custom_export(t_command *cmd);
int			msh_custom_unset(t_command *cmd);
int			msh_evaluate_env_if_exist(char **args, char **env);
void		msh_cmd(char **line);
char		*msh_get_env_by_key(char **env, char *argument);
void	    msh_struct_clear();
void		msh_sigint_handler_ch(int sig);
void		msh_sigint_handler(int sig_num);
void		msh_restore_signal(int sig);
void	    msh_pipex_sig(int sig);
void	    msh_child_sig(int sig);
void		msh_save_error_code(int code);
int			msh_read_error_code(void);
int			msh_perror(char *cmd_name);
int			msh_error_bash(char *message, char *str, int code);
char		**msh_concat_args(char **cmd, int size);
char		*msh_concat_str(char *arg, int size, char *insertion);
int			msh_buildins(t_command *cmd, int reg);
void		msh_exchange_token_value(t_command *cmd, int index);
void		msh_pipex_two_step(t_command *cmd, char **env);
int 		msh_executor(t_command *cmd, char **env, int *in_out_s);
void		msh_pipex_recursion(t_command *cmd, char **env);
void		msh_pipex_loop(t_command *cmd, char **env);
void    	msh_wait_pid(int pid);
void        msh_save_error_code(int code);

/**
 * @brief Execute commands with pipe or redirect
 * 
 * @param cmd List of commands
 * @param env  Evariables 
 */
char		**msh_create_env_var(char *new_var);
char		**msh_split(char *str, int c);
char		*msh_read_fd(int fd);

/**
 * @brief change path to relative if it necessary
 * 
 * @param cmd_name 	command name
 * @param env 		envaroment variable array
 * @return char* if command can be executed return new allocated string else return NULL
 */
char		*msh_get_path(char *cmd_name, char **env);
char		**msh_copy_env(char **array);
char		*msh_multy_pipe(t_command *cmds, char **env);
int			msh_check_special_signs(char *str, int *i, int *specials);
t_command	*msh_create_command(char    **dstr);
t_redirect	*msh_create_redirect(char *filepath, int specials);
t_arg		*msh_create_token(char *name, char *value, int order, int specials);
void		msh_add_redirect(t_redirect **current, char *value, t_specials specials);
int			msh_open(char *path, int type);
int			msh_export_invalid(char *arg);
int	    	msh_export_error(char *arg);
int			msh_multiple_iterator(int num, int *i, int sign);
void		msh_execution(t_command *cmd, char **env);
char		*msh_strncat(char *line, char *reall);
void		msh_sigint_handler(int sig_num);
char		*msh_get_str_inside(char *str, char *set, int reg);
void		msh_add_command(t_command **cur_cmd, char **value);
int			msh_is_token(char *arg);
int			msh_validate_line(char *line);
char        *msh_dollar_error_case(char **args, char *tmp);
char        *msh_evaluate_env_arg(char *arg, char **env);

/**
 * @brief Writes error message NOT ERRNO & clear struct & clear parsed string from readline
 * 
 * @param str string from readline
 * @param message error message
 */
int			msh_unexpected_token_error(char *token_str, int token_len);

/**
 * @brief 
 * 
 * @param env 
 * @param argument 
 * @return char* 
 */
char		*msh_get_env_by_key(char **env, char *argument);
int			msh_env_exist(char **env, char *argument);
int			msh_modify_env_var(char **env, char *new_value);
int         msh_specify_token(int *length, char *str, int specials);
char		*msh_token_quotes(char *str, int *index);
char		*msh_token_d_quotes(char *str, int *index);
char		*msh_token_dollar(char *str, int *index);
char		*msh_generate_tokens(int specials, int num);
t_arg		*msh_get_token_value(t_command *cmd, char *token);
char		*msh_dollar(char *str, int *index);
char		*msh_dollar_braces(char *str, int *index);
char		*msh_curl_braces(char *str, int *index);
int			msh_validation_redirs(char *str, int *i);
int			msh_conditions_d_quotes_close(char *str, int *i);
int			msh_conditions_quotes_close(char *str, int *i);
int			msh_conditions_quotes(char *str, int *i);
int			msh_conditions_d_quotes(char *str, int *i);
int			msh_conditions_dollar_braces(char *str, int *i);
int			msh_conditions_semicolon(char *str, int *i);
int			msh_conditions_pipe(char *str, int *i);
int			msh_conditions_eof(char *str, int *i);
int			msh_validation_closest_chars(char *str, int *i);
void		msh_side_effects(char **str, int *i, int *specials);
int     	msh_buildins_s(t_command *cmd);
void		msh_reflection_turn_on(void);
void        msh_redirects_fd(t_command *cmd);
int			msh_define_redirects(int *fd_arr, t_command *cmd);
int 	    msh_redirects_parse();

/**
 * @brief Check cmd if it is one of buildin functions
 * 
 * @param cmd command
 * @return int if success returns index from buildin arraylist else return -1 
 * */
int			msh_is_build(char *cmd);
void		msh_evaluate_all_tokens(t_command *cmd);
int			msh_make_path_relative(t_command *cmd);
void        msh_specials_replace(char **str, char *insertion, int *start, int end);

/**
 * @brief Cut's redirect signs, if they are clumped with filename or previos arg
 * j[0] = NULL	
 * j[1] = int of redirect < , > 
 * j[2] = index of another type of redirect if it exist in the string
 * j[3] = iterator for loop
 * @param i - current index of args
 * @param c - string with redirect
 */
void	    msh_cut_recursion(t_command *cmd, int i, char *c);

/**
 * @brief Cut current redirect & change next type for recursion
 * 
 * @param dest - redirect file name for adding in redirect struct
 * @param src  - income string or previos tail
 * @param tail - tail after first redirect
 * @param c - next type of redirect from list of  < , > , << , >>
 * @return int 1 - requirement to use recursion
 */
int         msh_first_redirect(t_command *cmd, int *i, char *c);

/**
 * @brief check command name if it not a dir
 * 
 * @param cmd current command to execute
 * @return int 1 TRUE; 0 FALSE;
 */
int	        msh_execution_validation(t_command *cmd);

/**
 * @brief 
 * 
 * @param arguments an array of arguments to look for in a variable environment
 * @param env variable environment
 * @return int returns index of var if true 0 if false
 */
int     	msh_env_exist(char **env, char *argument);

/**
 * @brief 
 * 
 * @param arg 
 * @param size  - size of whole str with nulls
 * @param insertion - string which need to be inserted
 * @return char* 
 */
char    	*msh_concat_str(char *arg, int size , char *insertion);

void	    msh_init_global_cmd();
t_command	*msh_last_cmd(void);
t_arg	    *msh_last_token(void);
void	    msh_add_token(t_command *cmd, t_arg *arg);
void	    msh_side_effect(char **str, int *i, int *specials);
int         msh_conditions_dollar(char *str, int *i);
void	    msh_specials_cut(char **str, int *i, int end);
//; | < > space
char        *msh_get_prev_word(char *str, int length, char *set);
char        *msh_get_next_word(char *str, int length, char *set);
void        msh_replace_null_arg(t_command *cmd);
char	    *msh_slash(char *str, int *index);
int         msh_conditions_slash(char *str, int *i);
int			msh_preparings(t_command *cmd);
int         msh_conditions_d_pipe(char *str, int *i);
int         msh_conditions_d_amp(char *str, int *i);
int         msh_conditions_curl_braces(char *str, int *i);
char        *msh_tokens_pseudo(int sp);
char        *msh_tokens_pseudo_dev(int sp);
char        *msh_token_wild_card(char *str, int *i);

#endif
