/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwulfe <dwulfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 11:56:00 by dwulfe            #+#    #+#             */
/*   Updated: 2022/01/21 16:51:15 by dwulfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "libs.h"

typedef enum s_specials
{
	NONE = -1,
	SEMICOLON = 1,		
	PIPE,
	AMPERSAND,
	REDIRECT,
	R_REDIRECT,
	D_REDIRECT,
	HEREDOC,
	R_REDIRECT_AMP,
	RD_REDIRECT_AMP,
	DOUBLE_PIPE,
	DOUBLE_AMP,
	S_QOUTES,
	QUOTES,
	D_QUOTES,
	CURL_BRACES,
	DOLLAR_BRACES,
	DOLLAR,
	SLASH,
	WILDCARD,
	ERROR
}				t_specials;

typedef struct s_redirect
{
	char				*file;
	t_specials			specials;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}				t_redirect;

typedef struct s_fd
{
	int			in;
	int			out;
	int			err;				
}				t_fd;

typedef struct s_arg
{
	int				order;
	int				has_prefix;
	int				is_prefix;
	char			*value;
	char			*pseudo;
	char			*name;
	t_specials		specials;
	struct s_arg	*next;
	struct s_arg	*prev;
}				t_arg;

typedef struct s_command
{
	int					num_args;
	char				**args;
	t_redirect			*out;
	t_redirect			*input;
	t_redirect			*err;
	t_redirect			*redirects;
	t_arg				*args_token;
	t_fd				*std;
	int					build;
	int					piped;
	int					background;
	t_specials			specials;

	struct s_command	*next;
	struct s_command	*prev;
}					t_command;

typedef char	*(*t_f_special)(char *str, int *length);
typedef int		(*t_f_condition)(char *str, int *length);

typedef struct s_info
{
	char			*pwd;
	int				exit_code;
	int				num_of_commands;
	int				num_token;
	char			**env;
	char			*f[8];
	t_command		*cur_cmd;
	t_f_special		func[20];
	t_f_condition	condition[16];
}				t_info;

t_info			g_info;

#endif