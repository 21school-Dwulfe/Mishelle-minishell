#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"
#include "features.h"

void	    msh_parse(char *str);
int 	    msh_help_parse_redirect(t_command *cmd, char *str, int *length, char *c);
void	    msh_add_to_struct(char **result);
void	    msh_add_command(t_command **cur_cmd, char **value);
int 	    msh_custom_exit(t_command *cmd);
int 	    msh_custom_pwd(t_command *cmd);
int 	    msh_custom_echo(t_command *cmd);
int 	    msh_custom_env(t_command *cmd);
int 	    msh_custom_cd(t_command *cmd);
int 	    msh_custom_export(t_command *cmd);
int 	    msh_custom_unset(t_command *cmd);
void	    msh_evaluate_env_call_if_exist(t_command *cmd, char **env);
void	    msh_cmd(char *line);
void	    msh_struct_clear();
int 	    msh_common_parse();
char		*msh_get_env_by_key(char **env, char *argument);
void		msh_sigint_handler_ch(int sig);
void		msh_sigint_handler(int sig_num);
void		msh_signal_child(int sig);
void	    msh_save_error_code(int code);
int 	    msh_read_error_code(void);
int	        msh_perror(char *cmd_name);
/**
 * @brief Execute commands with pipe or redirect
 * 
 * @param cmd List of commands
 * @param env  Evariables 
 */
void	    msh_config(int argc, char **argv, char **env);
char	    **msh_create_env_var(char *new_var);
char	    **msh_split(char *str, int c);
char        *msh_read_fd(int fd);
char        *msh_get_path(char *cmd_name, char **env);
char	    **msh_copy_env(char **array);
char        *msh_multy_pipe(t_command *cmds, char **env);
int	        msh_check_special_signs(char *str, int *i, int *specials);
t_command	*msh_create_command(char    **dstr);
void        msh_add_redirect(t_redirect **current, char *value, t_specials specials);
int         msh_open(char *path, int type);
int         msh_export_invalid(char *arg);
void	    msh_export_error(char *arg);
int			msh_multiple_iterator(int num, int *i, int sign);
void	    msh_execution(t_command *cmd, char **env, int *fd_pipe, int *fd_s);
char	    *msh_strlcat(char *line, char *buff, char *reall);
void        msh_sigint_handler(int sig_num);
/**
 * @brief Writes error message NOT ERRNO & clear struct & clear parsed string from readline
 * 
 * @param str string from readline
 * @param message error message
 */
void	    msh_redirect_error(char *message, char *token_str, int token_len);
char        *msh_get_env_by_key(char **env, char *argument);
int         msh_env_str(char **env, char *argument);
int         msh_modify_env_var(char **env, char *new_value);
#endif
