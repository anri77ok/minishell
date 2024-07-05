#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

void    pwd(int fd)
{
    char current_directory[PATH_MAX];

    if (getcwd(current_directory, PATH_MAX) == NULL)
	{}
		//error
	fd_put_string(current_directory, fd);
	write (fd, "\n", 1);
}