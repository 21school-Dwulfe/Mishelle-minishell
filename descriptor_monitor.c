#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ERR_ARG "\n\nWhat a fuck are you enter?! ONLY one argument -> PATHFILE\n"

int ft_error(char *mes)
{
    int i = 0;

    while (mes[i])
    {
        i++;
    }
    write(2, mes, i);
    return (1);
}

int main(int argc, char **argv)
{
    FILE    *file;

    if (argc != 2)
        return (ft_error(ERR_ARG));
    if ((file = fopen(argv[1], 'r')))
    
    return (0);
}