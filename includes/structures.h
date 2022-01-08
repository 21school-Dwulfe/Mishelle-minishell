#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libs.h"


// #ifndef QOUTES_ADD_REGIME
// # define QOUTES_ADD_REGIME 0
// #endif

typedef enum s_specials
{
	NONE = -1,
	SEMICOLON = 1, 		/* ; */
	PIPE,				/* | */
	AMPERSAND,			// &
	REDIRECT,			// >
	R_REDIRECT,			// <
	D_REDIRECT,			// >>
	RD_REDIRECT,		// <<
	R_REDIRECT_AMP,		// >&
	RD_REDIRECT_AMP,	// <&
	BIN_OR,				// ||
	BIN_AND,			// &&
	S_QOUTES,			// ``
	QUOTES,				// ''
	D_QUOTES,			// ""
	CURL_BRACES,		// ()
	DOLLAR_BRACES,		// $()
	DOLLAR,				// $
	ERROR = 18,		// 18+ Error in syntax (P.S Oh, damn, you are crazy person)
}				t_specials;

typedef struct s_redirect
{
	
	char				*file;
	t_specials			specials;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}				t_redirect;

typedef struct s_arg
{
	int				order; 			// index of arg to swap values
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
	int					num_args;		// количество аргументов включая команду 
	char				**args;			// массив строк где 0 индекс всегда является названием команды, остальные являются аргументами команды, заканчивается '\0'
	t_redirect			*out;			// путь к файлу для редиректа (запись)
	t_redirect			*input;			// путь к файлу для редиректа (чтение)
	t_redirect			*err;			// путь к файлу для редиректа (ошибок) 
	t_redirect			*redirects;		// oбший список редиректов
	t_arg				*args_token;	// tokens
	int					build;			// buildin function flag
	int					piped;			// вмето булевого значения флаг указывающи на наличие pipe
	int					background;
	t_specials			specials;		// переменная которая хранит тип специального знака ( >> ,  << ,  > ,  < ) для опрееления логики исполнения редиректа

	struct s_command	*next;			// указатель на сдедующуу команду
	struct s_command	*prev;			// указатель на предыдущюю команду (возможно не нужен)
}					t_command;

typedef char *(*f_special)(char *str, int *length);
typedef int (*f_condition)(char *str, int *length);

typedef struct	s_info
{
	char		*pwd;					// pwd for msh recursion
	int			exit_code;				// код ошибки
	int			num_of_commands;		// общее число команд
	int			num_token;				// count of tokens in shell
	char		odd_quote;				// тип незакрытой кавычки 			
	char		**env;					// переменное окружение минишелла (используется вместо стандартных функций редактирования окружения)
	char		*f[8];					// buildin names
	t_command   *cur_cmd;				// указатель на первую команду
	f_special	func[20];				// char *(*f_special)(char *str, int *length) -> function to do something specials with token parsing
	f_condition	condition[12];			// conditions for additional parsing logic
}				t_info;

t_info	g_info;

#endif