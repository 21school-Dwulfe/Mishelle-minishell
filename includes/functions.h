#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"
#include "features.h"

void	    msh_parse(char *str);
void	    msh_help_parse_semi(char *str, int length);
void	    msh_help_parse_pipe(char *str, int length);
void	    msh_help_parse_redirect(char *str, int length);
void	    msh_help_parse_r_redirect(char *str, int length);
void	    msh_help_parse_d_quotes(char *str, int length);
void	    msh_help_parse_quotes(char *str, int length);
void	    msh_help_parse_ampersand(char *str, int length);
void	    msh_help_parse_d_redirect(char *str, int length);
void	    msh_help_parse_rd_redirect(char *str, int length);
void	    msh_help_parse_r_redirect_amp(char *str, int length);
void	    msh_help_parse_rd_redirect_amp(char *str, int length);
void	    msh_add_to_struct(char **result);
void	    msh_add_command(t_command **cur_cmd, char **value);
void	    msh_custom_exit(t_command *cmd);
void	    msh_custom_pwd(t_command *cmd);
void	    msh_custom_echo(t_command *cmd);
void	    msh_custom_env(t_command *cmd);
void	    msh_custom_cd(t_command *cmd);
void	    msh_custom_export(t_command *cmd);
void	    msh_custom_unset(t_command *cmd);
void	    msh_evaluate_env_call_if_exist(t_command *cmd, char **env);
void	    msh_cmd(char *line);
void	    msh_struct_clear();

/**
 * @brief Execute commands with pipe or redirect
 * 
 * @param cmd List of commands
 * @param env  Evariables 
 */
void	    msh_execute(t_command *cmd, char **env);
void	    msh_config(int argc, char **argv, char **env);
char	    **msh_create_env_var(char *new_var);
char	    **msh_split(char *str, int c);
char        *msh_get_path(char *cmd_name, char **env);
char	    **msh_copy_env(char **array);
char        *msh_multy_pipe(t_command *cmds, char **env);
int	        msh_check_special_signs(char *str, int *i, int *specials);
t_command	*msh_create_command(char    **dstr);
void        msh_add_redirect(t_redirect **current, char *value);
int         msh_open(char *path, int type);

/**
 * @brief Writes error message NOT ERRNO & clear struct & clear parsed string from readline
 * 
 * @param str string from readline
 * @param message error message
 */
void	msh_error(char *str, char *message, char *token_str, int token_len);


#endif
