#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libs.h"

typedef int(*f)(char *str, int *length);

typedef enum s_specials
{
	SEMICOLON = 1, 		/* ; */
	PIPE,				/* | */
	AMPERSAND,			// &
	REDIRECT,			// >
	R_REDIRECT,			// <
	D_REDIRECT,			// >>
	RD_REDIRECT,		// <<
	R_REDIRECT_AMP,		// >&
	RD_REDIRECT_AMP,	// <&
	ERROR				// Error in syntax
}				t_specials;

typedef struct s_redirect
{
	char				*file;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}				t_redirect;


typedef struct s_command
{  
	int					num_args;  	// количество аргументов включая команду 
	char				**args;			// массив строк где 0 индекс всегда является названием команды, остальные являются аргументами команды, заканчивается '\0'
	t_redirect			*out;			// путь к файлу для редиректа (запись)
	t_redirect			*input;			// путь к файлу для редиректа (чтение)
	t_redirect			*err;			// путь к файлу для редиректа (ошибок) 
	int					piped;			// вмето булевого значения флаг указывающи на наличие pipe
	int					background;	
	t_specials			specials;		// переменная которая хранит тип специального знака ( >> ,  << ,  > ,  < ) для опрееления логики исполнения редиректа
	struct s_command	*next;			// указатель на сдедующуу команду
	struct s_command	*prev;			// указатель на предыдущюю команду (возможно не нужен)
}					t_command;

typedef struct	s_info
{
	int			num_of_commands;		// общее число команд
	char		odd_quote;				// тип незакрытой кавычки 			
	char		**env;					// переменное окружение минишелла (используется вместо стандартных функций редактирования окружения)
	t_command   *cur_cmd; 		// указатель на первую команду
	f			func[16];				// массив функций для реализации доп логики (возможно не пригодится)
}				t_info;

t_info	g_info;

#endif