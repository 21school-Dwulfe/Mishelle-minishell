#include "../includes/main.h"

int msh_open(char *path, int type)
{
    if (type == REDIRECT)
    {
        return (open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU));
    }
    else if (type == D_REDIRECT)
    {
        return (open(path, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU));
    }
    else if (type == R_REDIRECT)
    {
        return (open(path, O_RDONLY));
    }
    else //if (type == RD_REDIRECT)
    {
        return (open(path, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU));
    }
}