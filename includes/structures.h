#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "libs.h"

typedef struct	s_s_comand
{
	int		num_of_available_args;
	int		num_of_args;
	char	*name;
	char	**arguments;

}				t_s_command;

typedef struct s_command
{ 
	int numberOfAvailableSimpleCommands; 
	int num_of_simple_commands; 
	t_s_command **simple_commands; 
	char *outFile;
	char *inputFile;
	char *errFile;
	int background;
	void *prompt; 
	void *print; 
	void *execute; 
	void *clear;

}					t_command;

typedef struct	s_info
{
	char		is_odd_single_quatations;
	char		is_odd_double_quatations;
	char		odd_quote;
	t_command   *currentCommand; // для команд с пайпами или редиректами
	t_s_command *currentSimpleCommand; //для команд без пайпов и редиректов

}				t_info;

t_info	g_info;

#endif