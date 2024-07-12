#include "minishell.h"
#include "tokenization.h"
#include "utils.h"
#include "env.h"
#include "pipex.h"

int    pwd(int fd, int *is_builtin)
{
    char current_directory[PATH_MAX];

	*is_builtin = 1;
    if (getcwd(current_directory, PATH_MAX) == NULL)
	{
		//erroni hamar teqst
		return (1);//esi mer komica arvac bashi vaxt exit error-@ 1 chi//by Narek
	}
	fd_put_string(current_directory, fd);
	write (fd, "\n", 1);
	return (0);
}
