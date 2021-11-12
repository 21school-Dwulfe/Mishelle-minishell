#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libs.h"

typedef void(*f)(char *str, int *length);

typedef enum s_specials
{
	SEMICOLON,
	PIPE,
	REDIRECT,
	R_REDIRECT,
	D_REDIRECT,
	RD_REDIRECT,
	R_REDIRECT_AMP,
	RD_REDIRECT_AMP,
	AMPERSAND,
	ERROR
}				t_specials;



typedef struct s_command
{ 
	int					numberOfAvailableArgs; 
	char				**arguments;
	char				*out_file;
	char				*input_file;
	char				*errFile;
	int					piped;
	t_specials			specials;
	int					background;
	struct s_command	*next;
	struct s_command	*prev;
	// void *prompt;
	// void *print;
	// void *execute;
	// void *clear;

}					t_command;

typedef struct	s_info
{
	int			num_of_commands; 
	char		is_odd_single_quatations;
	char		is_odd_double_quatations;
	char		odd_quote;
	short		regime;
	char		**env;
	t_command   *current_command; 
	f			func[16];
}				t_info;

t_info	g_info;

#endif