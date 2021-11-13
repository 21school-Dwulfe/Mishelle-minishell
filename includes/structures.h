#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libs.h"

typedef void(*f)(char *str, int *length);

typedef enum s_specials
{
	SEMICOLON, 			// ;
	PIPE,				// |
	REDIRECT,			// >
	R_REDIRECT,			// <
	D_REDIRECT,			// >>
	RD_REDIRECT,		// <<
	R_REDIRECT_AMP,		// >&
	RD_REDIRECT_AMP,	// <&
	AMPERSAND,			// &
	ERROR				// Error in synax
}				t_specials;

typedef struct s_command
{  
	int					number_args;  	// количество аргументов включая команду 
	char				**arguments;	// массив строк где 0 индекс всегда является названием команды, остальные являются аргументами команды, заканчивается '\0'
	char				*out_file;		// путь к файлу для редиректа (запись)
	char				*input_file;	// путь к файлу для редиректа (чтение)
	char				*err_file;		// путь к файлу для редиректа (ошибок) 
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
	t_command   *current_command; 		// указатель на первую команду
	f			func[16];				// массив функций для реализации доп логики (возможно не пригодится)
}				t_info;

t_info	g_info;

#endif